#include "Global.h"
#include "ll/api/event/EventBus.h"
#include "mc/world/inventory/network/ItemStackRequestActionTransferBase.h"
using namespace ll::hash_utils;

class LegacyScriptEventManager {
private:
    int64                                              mNextEventId = 0;
    std::unordered_map<uint64, ll::event::ListenerPtr> mEventListeners;

public:
    std::string getNextEventId() {
        mNextEventId++;
        return "GMLIB_EVENT_" + std::to_string(mNextEventId);
    }

    void emplaceListener(std::string const& scriptEventId, ll::event::ListenerPtr listenerPtr) {
        mEventListeners[doHash(scriptEventId)] = listenerPtr;
    }

    void removeListener(std::string const& scriptEventId) {
        ll::event::EventBus::getInstance().removeListener(mEventListeners[doHash(scriptEventId)]);
        mEventListeners.erase(doHash(scriptEventId));
    }

public:
    static LegacyScriptEventManager& getInstance() {
        static std::unique_ptr<LegacyScriptEventManager> instance;
        if (!instance) {
            instance = std::make_unique<LegacyScriptEventManager>();
        }
        return *instance;
    }
};

#define REGISTER_EVENT_LISTEN(eventType, callFunction, eventParams, cancelFunction, otherFunction)                     \
    eventManager.emplaceListener(                                                                                      \
        eventId,                                                                                                       \
        eventBus.emplaceListener<eventType>([eventName, eventId, &eventBus, &eventManager](eventType& ev) -> void {    \
            if (!RemoteCall::hasFunc(eventName, eventId)) {                                                            \
                eventManager.removeListener(eventId);                                                                  \
                return;                                                                                                \
            }                                                                                                          \
            bool result = true;                                                                                        \
            try {                                                                                                      \
                otherFunction;                                                                                         \
                result = RemoteCall::importAs<bool callFunction>(eventName, eventId) eventParams;                      \
            } catch (...) {}                                                                                           \
            if (!result) cancelFunction;                                                                               \
        })                                                                                                             \
    );                                                                                                                 \
    return true;

void Export_Event_API() {
    RemoteCall::exportAs("GMLIB_Event_API", "getNextScriptEventId", []() -> std::string {
        return LegacyScriptEventManager::getInstance().getNextEventId();
    });
    auto& eventBus     = ll::event::EventBus::getInstance();
    auto& eventManager = LegacyScriptEventManager::getInstance();
    RemoteCall::exportAs(
        "GMLIB_Event_API",
        "callCustomEvent",
        [&eventBus, &eventManager](std::string const& eventName, std::string const& eventId) -> bool {
            if (!RemoteCall::hasFunc(eventName, eventId)) return false;
            switch (doHash(eventName)) {
            case doHash("onClientLogin"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::packet::ClientLoginAfterEvent,
                    (std::string const& realName,
                     std::string const& uuid,
                     std::string const& serverXuid,
                     std::string const& clientXuid),
                    (ev.getRealName(), ev.getUuid().asString(), ev.getServerAuthXuid(), ev.getClientAuthXuid()),
                    logger.error("Event \"onClientLogin\" cannot be intercepted"),
                );
            }
            case doHash("onWeatherChange"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::level::WeatherUpdateBeforeEvent,
                    (int lightningLevel, int rainLevel, int lightningLast, int rainLast),
                    (ev.getLightningLevel(), ev.getRainLevel(), ev.getLightningLastTick(), ev.getRainingLastTick()),
                    ev.cancel(),
                );
            }
            case doHash("onMobPick"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::entity::MobPickupItemBeforeEvent,
                    (::Actor * mob, ::Actor * item),
                    (&ev.self(), (::Actor*)&ev.getItemActor()),
                    ev.cancel(),
                );
            }
            case doHash("onItemTrySpawn"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::entity::ItemActorSpawnBeforeEvent,
                    (const ::ItemStack* item, std::pair<Vec3, int> position, int64 spawnerUniqueId),
                    (&ev.getItem(),
                     {ev.getPosition(), ev.getBlockSource().getDimensionId().id},
                     ev.getSpawner().has_value() ? ev.getSpawner()->getOrCreateUniqueID().id : -1),
                    ev.cancel(),
                );
            }
            case doHash("onItemSpawned"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::entity::ItemActorSpawnAfterEvent,
                    (const ::ItemStack* item, ::Actor* itemActor, std::pair<Vec3, int> position, int64 spawnerUniqueId),
                    (&ev.getItem(),
                     (::Actor*)&ev.getItemActor(),
                     {ev.getPosition(), ev.getBlockSource().getDimensionId().id},
                     ev.getSpawner().has_value() ? ev.getSpawner()->getOrCreateUniqueID().id : -1),
                    logger.error("Event \"onItemSpawned\" cannot be intercepted"),
                );
            }
            case doHash("onEntityTryChangeDim"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::entity::ActorChangeDimensionBeforeEvent,
                    (::Actor * entity, int toDimId),
                    (&ev.self(), ev.getToDimensionId()),
                    ev.cancel(),
                );
            }
            case doHash("onLeaveBed"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::player::PlayerStopSleepBeforeEvent,
                    (::Player * pl),
                    (&ev.self()),
                    ev.cancel(),
                );
            }
            case doHash("onDeathMessage"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::entity::DeathMessageAfterEvent,
                    (std::string const& message, std::vector<std::string>, ::Actor* dead),
                    (ev.getDeathMessage().first, ev.getDeathMessage().second, &ev.self()),
                    logger.error("Event \"onDeathMessage\" cannot be intercepted"),
                );
            }
            case doHash("onMobHurted"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::entity::MobHurtAfterEvent,
                    (::Actor * mob, ::Actor * source, float damage, int cause),
                    (&ev.self(), source, ev.getDamage(), (int)damageSource.getCause()),
                    logger.error("Event \"onMobHurted\" cannot be intercepted"),
                    auto& damageSource = ev.getSource();
                    ::Actor* source    = nullptr;
                    if (damageSource.isEntitySource()) {
                        auto uniqueId = damageSource.getDamagingEntityUniqueID();
                        source        = ll::service::getLevel()->fetchEntity(uniqueId);
                        if (source->getOwner()) source = source->getOwner();
                    }
                );
            }
            case doHash("onEndermanTake"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::entity::EndermanTakeBlockBeforeEvent,
                    (::Actor * mob),
                    (&ev.self()),
                    ev.cancel(),
                );
            }
            case doHash("onEntityChangeDim"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::entity::ActorChangeDimensionAfterEvent,
                    (::Actor * mob, int fromDimId),
                    (&ev.self(), ev.getFromDimensionId()),
                    logger.error("Event \"onEntityChangeDim\" cannot be intercepted"),
                );
            }
            case doHash("onDragonRespawn"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::entity::DragonRespawnBeforeEvent,
                    (int64 enderDragonUniqueID),
                    (ev.getEnderDragon().id),
                    ev.cancel(),
                )
            }
            case doHash("onProjectileTryCreate"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::entity::ProjectileCreateBeforeEvent,
                    (::Actor * mob, int64 uniqueId),
                    (&ev.self(), ev.getShooter() ? ev.getShooter()->getOrCreateUniqueID().id : -1),
                    ev.cancel(),
                );
            }
            case doHash("onProjectileCreate"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::entity::ProjectileCreateAfterEvent,
                    (::Actor * mob, int64 uniqueId),
                    (&ev.self(), ev.getShooter() ? ev.getShooter()->getOrCreateUniqueID().id : -1),
                    logger.error("Event \"onProjectileCreate\" cannot be intercepted"),
                );
            }
            case doHash("onSpawnWanderingTrader"): {
                REGISTER_EVENT_LISTEN(
                    gmlib::event::entity::SpawnWanderingTraderBeforeEvent,
                    (std::pair<BlockPos, int> pos),
                    ({ev.getPos(), ev.getRegion().getDimensionId()}),
                    ev.cancel(),
                );
            }
            case doHash("onHandleRequestAction"): {
                REGISTER_EVENT_LISTEN(gmlib::event::player::HandleRequestActionBeforeEvent,
                                      (::Player * player,
                                       std::string const& actionType,
                                       int                count,
                                       std::string const& sourceContainerNetId,
                                       int                sourceSlot,
                                       std::string const& destinationContainerNetId,
                                       int                destinationSlot),
                                      ((::Player*)&ev.self(),
                                       magic_enum::enum_name(requestAction->mActionType).data(),
                                       (int)requestAction->mAmount,
                                       magic_enum::enum_name(requestAction->mSrc.mOpenContainerNetId).data(),
                                       (int)requestAction->mSrc.mSlot,
                                       magic_enum::enum_name(requestAction->mDst.mOpenContainerNetId).data(),
                                       (int)requestAction->mDst.mSlot),
                                      ev.cancel(),
                                      auto requestAction = (ItemStackRequestActionTransferBase*)&ev.getRequestAction();
                );
            }
            case doHash("onSendContainerClosePacket"): {
                REGISTER_EVENT_LISTEN(
                    event::packet::ContainerClosePacketSendAfterEvent,
                    (::Player * player, int ContainerNetId),
                    (ev.getServerNetworkHandler()
                         .getServerPlayer(ev.getNetworkIdentifier(), ev.getPacket().mClientSubId),
                     (int)ev.getPacket().mContainerId),
                    logger.error("Event \"onSendContainerClosePacket\" cannot be intercepted"),
                )
            }
            case doHash("onServerStopping"): {
                REGISTER_EVENT_LISTEN(
                    ll::event::server::ServerStoppingEvent,
                    (),
                    (),
                    logger.error("Event \"onServerStopping\" cannot be intercepted"),
                );
            }
            default:
                return false;
            }
        }
    );
}