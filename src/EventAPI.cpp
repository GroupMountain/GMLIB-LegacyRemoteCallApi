#include "Global.h"
using namespace ll::hash_utils;

class EventManager {
private:
    std::unordered_map<ullong, ll::event::ListenerPtr> mEventIds;

public:
    static EventManager& getInstance() {
        static std::unique_ptr<EventManager> instance;
        if (!instance) instance = std::make_unique<EventManager>();
        return *instance;
    }

    ullong getNextId() {
        auto id = mEventIds.size();
        mEventIds.emplace(id, nullptr);
        return id;
    }

    bool addListener(ullong id, ll::event::ListenerPtr const& listener) {
        if (mEventIds.contains(id) && mEventIds[id]) return false;
        mEventIds[id] = listener;
        return true;
    }

    bool removeListener(ullong id) {
        if (ll::event::EventBus::getInstance().removeListener(mEventIds[id])) {
            mEventIds[id] = nullptr;
            return true;
        }
        return false;
    }

    bool hasListener(ullong id) { return mEventIds.contains(id) && mEventIds[id]; }

    ll::event::ListenerPtr getListener(ullong id) { return mEventIds.contains(id) ? mEventIds[id] : nullptr; }
};

#define REGISTER_EVENT_LISTEN(eventType, paramType, params, cancelFun, ...)                                            \
    auto eventPtr = ll::event::EventBus::getInstance().emplaceListener<eventType>(                                     \
        [pluginName, eventName, eventId](eventType& event) -> void {                                                   \
            if (!RemoteCall::hasFunc(pluginName, eventName + "_" + std::to_string(eventId))) {                         \
                EventManager::getInstance().removeListener(eventId);                                                   \
                return;                                                                                                \
            }                                                                                                          \
            try {                                                                                                      \
                __VA_ARGS__                                                                                            \
                auto result =                                                                                          \
                    RemoteCall::importAs<bool paramType>(pluginName, eventName + "_" + std::to_string(eventId))        \
                        params;                                                                                        \
                cancelFun                                                                                              \
            } catch (...) {}                                                                                           \
        },                                                                                                             \
        ll::event::EventPriority(priority)                                                                             \
    );                                                                                                                 \
    return eventId

void Export_Event_API() {
    RemoteCall::exportAs("GMLIB_Event_API", "removeListener", [](ll::event::ListenerId eventId) -> bool {
        return EventManager::getInstance().removeListener(eventId);
    });

    RemoteCall::exportAs("GMLIB_Event_API", "hasListener", [](ll::event::ListenerId eventId) -> bool {
        return EventManager::getInstance().hasListener(eventId);
    });

    RemoteCall::exportAs("GMLIB_Event_API", "getListenerPriority", [](ll::event::ListenerId eventId) -> int {
        if (auto event = EventManager::getInstance().getListener(eventId); event != nullptr) {
            return (int)event->getPriority();
        }
        return -1;
    });

    RemoteCall::exportAs(
        "GMLIB_Event_API",
        "emplaceListener",
        [](std::string const& pluginName, std::string const& eventName, int priority) -> llong {
            auto eventId = EventManager::getInstance().getNextId();
            switch (doHash(eventName)) {
            case doHash("ll::ServerStoppingEvent"): {
                REGISTER_EVENT_LISTEN(ll::event::ServerStoppingEvent, (), (), , );
            }
            case doHash("gmlib::ClientLoginAfterEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::PacketEvent::ClientLoginAfterEvent,
                    (std::string const& realName,
                     std::string const& uuid,
                     std::string const& serverXuid,
                     std::string const& clientXuid),
                    (event.getRealName(),
                     event.getUuid().asString(),
                     event.getServerAuthXuid(),
                     event.getClientAuthXuid()),
                    if (result) event.disConnectClient();
                );
            }
            case doHash("gmlib::WeatherUpdateBeforeEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::LevelEvent::WeatherUpdateBeforeEvent,
                    (float rainLevel, int rainTime, float lightningLevel, int lightningTime, bool isCancelled),
                    (event.getRainLevel(),
                     event.getRainingLastTick(),
                     event.getLightningLevel(),
                     event.getLightningLastTick(),
                     event.isCancelled()),
                    event.setCancelled(result);
                );
            }
            case doHash("gmlib::WeatherUpdateAfterEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::LevelEvent::WeatherUpdateAfterEvent,
                    (float rainLevel, int rainTime, float lightningLevel, int lightningTime),
                    (event.getRainLevel(),
                     event.getRainingLastTick(),
                     event.getLightningLevel(),
                     event.getLightningLastTick()),
                    ,
                );
            }
            case doHash("gmlib::MobPickupItemBeforeEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::MobPickupItemBeforeEvent,
                    (Actor * mob, Actor * item, bool isCancelled),
                    (&event.self(), (Actor*)&event.getItemActor(), event.isCancelled()),
                    event.setCancelled(result);
                );
            }
            case doHash("gmlib::MobPickupItemAfterEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::MobPickupItemAfterEvent,
                    (Actor * mob, Actor * item),
                    (&event.self(), (Actor*)&event.getItemActor()),
                    ,
                );
            }
            case doHash("gmlib::ItemActorSpawnBeforeEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::ItemActorSpawnBeforeEvent,
                    (ItemStack * item, std::pair<Vec3, int> position, int64 spawnerUniqueId, bool isCancelled),
                    (&event.getItem(),
                     {event.getPosition(), event.getBlockSource().getDimensionId().id},
                     event.getSpawner().has_value() ? event.getSpawner()->getOrCreateUniqueID().rawID : -1,
                     event.isCancelled()),
                    event.setCancelled(result);
                );
            }
            case doHash("gmlib::ItemActorSpawnAfterEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::ItemActorSpawnAfterEvent,
                    (Actor * item, std::pair<Vec3, int> position, int64 spawnerUniqueId),
                    (&event.self(),
                     {event.getPosition(), event.getBlockSource().getDimensionId().id},
                     event.getSpawner().has_value() ? event.getSpawner()->getOrCreateUniqueID().rawID : -1),
                    ,
                );
            }
            case doHash("gmlib::ActorChangeDimensionBeforeEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::ActorChangeDimensionBeforeEvent,
                    (Actor * entity, int toDimId, bool isCancelled),
                    (&event.self(), event.getToDimensionId(), event.isCancelled()),
                    event.setCancelled(result);
                );
            }
            case doHash("gmlib::ActorChangeDimensionAfterEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::ActorChangeDimensionAfterEvent,
                    (Actor * entity, int fromDimId, int toDimId),
                    (&event.self(), event.getFromDimensionId(), event.getToDimensionId()),
                    ,
                );
            }
            case doHash("gmlib::PlayerStartSleepBeforeEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::PlayerEvent::PlayerStartSleepBeforeEvent,
                    (Player * entity, BlockPos pos, bool isCancelled),
                    (&event.self(), event.getPosition(), event.isCancelled()),
                    event.setCancelled(result);
                );
            }
            case doHash("gmlib::PlayerStartSleepAfterEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::PlayerEvent::PlayerStartSleepAfterEvent,
                    (Player * entity, BlockPos pos, int result),
                    (&event.self(), event.getPosition(), (int)event.getResult()),
                    ,
                );
            }
            case doHash("gmlib::PlayerStopSleepBeforeEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::PlayerEvent::PlayerStopSleepBeforeEvent,
                    (Player * entity, bool forcefulWakeUp, bool updateLevelList, bool isCancelled),
                    (&event.self(), event.isForcefulWakeUp(), event.isUpdateLevelList(), event.isCancelled()),
                    event.setCancelled(result);
                );
            }
            case doHash("gmlib::PlayerStopSleepAfterEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::PlayerEvent::PlayerStopSleepAfterEvent,
                    (Player * entity, bool forcefulWakeUp, bool updateLevelList, bool),
                    (&event.self(), event.isForcefulWakeUp(), event.isUpdateLevelList(), false),
                    ,
                );
            }
            case doHash("gmlib::DeathMessageAfterEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::DeathMessageAfterEvent,
                    (std::string const& message, std::vector<std::string>, Actor* dead),
                    (event.getDeathMessage().first, event.getDeathMessage().second, &event.self()),
                    ,
                );
            }
            case doHash("gmlib::MobHurtAfterEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::MobHurtAfterEvent,
                    (Actor * mob, Actor * source, float damage, int cause),
                    (&event.self(), source, -event.getDamage(), (int)damageSource.getCause()),
                    ,
                    auto& damageSource = event.getSource();
                    Actor* source      = nullptr;
                    if (damageSource.isEntitySource()) {
                        auto uniqueId = damageSource.getDamagingEntityUniqueID();
                        source        = ll::service::getLevel()->fetchEntity(uniqueId, false);
                        if (source->getOwner()) source = source->getOwner();
                    }
                );
            }
            case doHash("gmlib::EndermanTakeBlockBeforeEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::EndermanTakeBlockBeforeEvent,
                    (Actor * mob, bool isCancelled),
                    (&event.self(), event.isCancelled()),
                    event.setCancelled(result);
                );
            }
            case doHash("gmlib::DragonRespawnBeforeEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::DragonRespawnBeforeEvent,
                    (bool isCancelled),
                    (event.isCancelled()),
                    event.setCancelled(result);
                );
            }
            case doHash("gmlib::DragonRespawnAfterEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::DragonRespawnAfterEvent,
                    (Actor * mob),
                    (event.getEnderDragon()),
                );
            }
            case doHash("gmlib::ProjectileCreateBeforeEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::ProjectileCreateBeforeEvent,
                    (Actor * mob, int64 uniqueId, bool isCancelled),
                    (&event.self(),
                     event.getShooter() ? event.getShooter()->getOrCreateUniqueID().rawID : -1,
                     event.isCancelled()),
                    event.setCancelled(result);
                );
            }
            case doHash("gmlib::ProjectileCreateAfterEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::ProjectileCreateAfterEvent,
                    (Actor * mob, int64 uniqueId),
                    (&event.self(), event.getShooter() ? event.getShooter()->getOrCreateUniqueID().rawID : -1),
                );
            }
            case doHash("gmlib::SpawnWanderingTraderBeforeEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::SpawnWanderingTraderBeforeEvent,
                    (std::pair<BlockPos, int> pos, bool isCancelled),
                    ({event.getPos(), event.getRegion().getDimensionId()}, event.isCancelled()),
                    event.setCancelled(result);
                );
            }
            case doHash("gmlib::SpawnWanderingTraderAfterEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::EntityEvent::SpawnWanderingTraderAfterEvent,
                    (std::pair<BlockPos, int> pos),
                    ({event.getPos(), event.getRegion().getDimensionId()}),
                );
            }
            case doHash("gmlib::HandleRequestActionBeforeEvent"): {
                // clang-format off
                    REGISTER_EVENT_LISTEN(
                        GMLIB::Event::PlayerEvent::HandleRequestActionBeforeEvent,
                        (
                            Player *           player,
                            std::string const& actionType,
                            int                count,
                            std::string const& sourceContainerNetId,
                            int                sourceSlot,
                            std::string const& destinationContainerNetId,
                            int                destinationSlot,
                            bool               isCancelled
                        ),
                        (
                            (Player*)&event.self(),
                            magic_enum::enum_name(requestAction.mActionType).data(),
                            (int)requestAction.mAmount,
                            magic_enum::enum_name(requestAction.mSrc->mFullContainerName.mName).data(),
                            (int)requestAction.mSrc->mSlot,
                            magic_enum::enum_name(requestAction.mDst->mFullContainerName.mName).data(),
                            (int)requestAction.mDst->mSlot,
                            event.isCancelled()
                        ),
                        event.setCancelled(result);,
                        auto& requestAction = (ItemStackRequestActionTransferBase&)event.getRequestAction();
                    );
                // clang-format on
            }
            case doHash("gmlib::HandleRequestActionAfterEvent"): {
                // clang-format off
                    REGISTER_EVENT_LISTEN(
                        GMLIB::Event::PlayerEvent::HandleRequestActionAfterEvent,
                        (
                            Player *           player,
                            std::string const& actionType,
                            int                count,
                            std::string const& sourceContainerNetId,
                            int                sourceSlot,
                            std::string const& destinationContainerNetId,
                            int                destinationSlot
                        ),
                        (
                            (Player*)&event.self(),
                            magic_enum::enum_name(requestAction.mActionType).data(),
                            (int)requestAction.mAmount,
                            magic_enum::enum_name(requestAction.mSrc->mFullContainerName.mName).data(),
                            (int)requestAction.mSrc->mSlot,
                            magic_enum::enum_name(requestAction.mDst->mFullContainerName.mName).data(),
                            (int)requestAction.mDst->mSlot
                        ),
                        ,
                        auto& requestAction = (ItemStackRequestActionTransferBase&)event.getRequestAction();
                    );
                // clang-format on
            }
            case doHash("gmlib::ContainerClosePacketSendAfterEvent"): {
                REGISTER_EVENT_LISTEN(
                    GMLIB::Event::PacketEvent::ContainerClosePacketSendAfterEvent,
                    (Player * player, int containerId, bool serverInitiatedClose, bool),
                    (event.getServerNetworkHandler()
                         ._getServerPlayer(event.getNetworkIdentifier(), event.getPacket().mClientSubId),
                     (int)event.getPacket().mContainerId,
                     event.getPacket().mServerInitiatedClose,
                     false),
                    ,
                );
            }
            }
            return -1;
        }
    );
}