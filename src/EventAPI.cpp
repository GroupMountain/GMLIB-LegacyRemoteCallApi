#include "Global.h"
using namespace ll::hash_utils;

void Export_Event_API() {
    auto eventBus = &ll::event::EventBus::getInstance();
    RemoteCall::exportAs(
        "GMLIB_API",
        "callCustomEvent",
        [eventBus](std::string const& eventName, std::string const& eventId) -> bool {
            if (!RemoteCall::hasFunc(eventName, eventId)) return false;
            switch (doHash(eventName)) {
            case doHash("onClientLogin"): {
                auto Call = RemoteCall::importAs<bool(
                    std::string const& realName,
                    std::string const& uuid,
                    std::string const& serverXuid,
                    std::string const& clientXuid
                )>(eventName, eventId);
                eventBus->emplaceListener<Event::PacketEvent::ClientLoginAfterEvent>(
                    [Call](Event::PacketEvent::ClientLoginAfterEvent& ev) {
                        try {
                            Call(
                                ev.getRealName(),
                                ev.getUuid().asString(),
                                ev.getServerAuthXuid(),
                                ev.getClientAuthXuid()
                            );
                        } catch (...) {}
                    }
                );
                return true;
            }
            case doHash("onWeatherChange"): {
                auto Call =
                    RemoteCall::importAs<bool(int lightningLevel, int rainLevel, int lightningLast, int rainLast)>(
                        eventName,
                        eventId
                    );
                eventBus->emplaceListener<Event::LevelEvent::WeatherUpdateBeforeEvent>(
                    [Call](Event::LevelEvent::WeatherUpdateBeforeEvent& ev) {
                        bool result = true;
                        try {
                            result = Call(
                                ev.getLightningLevel(),
                                ev.getRainLevel(),
                                ev.getLightningLastTick(),
                                ev.getRainingLastTick()
                            );
                        } catch (...) {}
                        if (!result) {
                            ev.cancel();
                        }
                    }
                );
                return true;
            }
            case doHash("onMobPick"): {
                auto Call = RemoteCall::importAs<bool(Actor * mob, Actor * item)>(eventName, eventId);
                eventBus->emplaceListener<Event::EntityEvent::MobPickupItemBeforeEvent>(
                    [Call](Event::EntityEvent::MobPickupItemBeforeEvent& ev) {
                        bool result = true;
                        try {
                            result = Call(&ev.self(), (Actor*)&ev.getItemActor());
                        } catch (...) {}
                        if (!result) {
                            ev.cancel();
                        }
                    }
                );
                return true;
            }
            case doHash("onItemTrySpawn"): {
                auto Call =
                    RemoteCall::importAs<bool(const ItemStack* item, std::pair<Vec3, int> position, Actor* spawner)>(
                        eventName,
                        eventId
                    );
                eventBus->emplaceListener<Event::EntityEvent::ItemActorSpawnBeforeEvent>(
                    [Call](Event::EntityEvent::ItemActorSpawnBeforeEvent& ev) {
                        auto                 pos    = ev.getPosition();
                        auto                 dimid  = ev.getBlockSource().getDimensionId().id;
                        std::pair<Vec3, int> lsePos = {pos, dimid};
                        bool                 result = true;
                        try {
                            result = Call(&ev.getItem(), lsePos, ev.getSpawner());
                        } catch (...) {}
                        if (!result) {
                            ev.cancel();
                        }
                    }
                );
                return true;
            }
            case doHash("onItemSpawned"): {
                auto Call = RemoteCall::importAs<
                    bool(const ItemStack* item, Actor* itemActor, std::pair<Vec3, int> position, Actor* spawner)>(
                    eventName,
                    eventId
                );
                eventBus->emplaceListener<Event::EntityEvent::ItemActorSpawnAfterEvent>(
                    [Call](Event::EntityEvent::ItemActorSpawnAfterEvent& ev) {
                        auto                 pos    = ev.getPosition();
                        auto                 dimid  = ev.getBlockSource().getDimensionId().id;
                        std::pair<Vec3, int> lsePos = {pos, dimid};
                        try {
                            Call(&ev.getItem(), (Actor*)&ev.getItemActor(), lsePos, ev.getSpawner());
                        } catch (...) {}
                    }
                );
                return true;
            }
            case doHash("onEntityChangeDim"): {
                auto Call = RemoteCall::importAs<bool(Actor * entity, int toDimId)>(eventName, eventId);
                eventBus->emplaceListener<Event::EntityEvent::ActorChangeDimensionBeforeEvent>(
                    [Call](Event::EntityEvent::ActorChangeDimensionBeforeEvent& ev) {
                        bool result = true;
                        try {
                            result = Call(&ev.self(), ev.getToDimensionId());
                        } catch (...) {}
                        if (!result) {
                            ev.cancel();
                        }
                    }
                );
                return true;
            }
            case doHash("onLeaveBed"): {
                auto Call = RemoteCall::importAs<bool(Player * pl)>(eventName, eventId);
                eventBus->emplaceListener<Event::PlayerEvent::PlayerStopSleepBeforeEvent>(
                    [Call](Event::PlayerEvent::PlayerStopSleepBeforeEvent& ev) {
                        bool result = true;
                        try {
                            result = Call(&ev.self());
                        } catch (...) {}
                        if (!result) {
                            ev.cancel();
                        }
                    }
                );
                return true;
            }
            case doHash("onDeathMessage"): {
                auto Call =
                    RemoteCall::importAs<bool(std::string const& message, std::vector<std::string>, Actor* dead)>(
                        eventName,
                        eventId
                    );
                eventBus->emplaceListener<Event::EntityEvent::DeathMessageAfterEvent>(
                    [Call](Event::EntityEvent::DeathMessageAfterEvent& ev) {
                        auto msg    = ev.getDeathMessage();
                        auto source = ev.getDamageSource();
                        try {
                            Call(msg.first, msg.second, &ev.self());
                        } catch (...) {}
                    }
                );
                return true;
            }
            case doHash("onMobHurted"): {
                auto Call = RemoteCall::importAs<bool(Actor * mob, Actor * source, float damage, int cause)>(
                    eventName,
                    eventId
                );
                eventBus->emplaceListener<Event::EntityEvent::MobHurtAfterEvent>(
                    [Call](Event::EntityEvent::MobHurtAfterEvent& ev) {
                        auto&  damageSource = ev.getSource();
                        Actor* source       = nullptr;
                        if (damageSource.isEntitySource()) {
                            auto uniqueId = damageSource.getDamagingEntityUniqueID();
                            source        = ll::service::getLevel()->fetchEntity(uniqueId);
                            if (source->getOwner()) {
                                source = source->getOwner();
                            }
                        }
                        try {
                            Call(&ev.self(), source, ev.getDamage(), (int)damageSource.getCause());
                        } catch (...) {}
                    }
                );
                return true;
            }
            case doHash("onEndermanTake"): {
                auto Call = RemoteCall::importAs<bool(Actor * mob)>(eventName, eventId);
                eventBus->emplaceListener<Event::EntityEvent::EndermanTakeBlockBeforeEvent>(
                    [Call](Event::EntityEvent::EndermanTakeBlockBeforeEvent& ev) {
                        bool result = true;
                        try {
                            result = Call(&ev.self());
                        } catch (...) {}
                        if (!result) {
                            ev.cancel();
                        }
                    }
                );
                return true;
            }
            case doHash("onEntityChangeDimAfter"): {
                auto Call = RemoteCall::importAs<bool(Actor * mob, int fromDimId)>(eventName, eventId);
                eventBus->emplaceListener<Event::EntityEvent::ActorChangeDimensionAfterEvent>(
                    [Call](Event::EntityEvent::ActorChangeDimensionAfterEvent& ev) {
                        bool result = true;
                        try {
                            result = Call(&ev.self(), ev.getFromDimensionId());
                        } catch (...) {}
                    }
                );
                return true;
            }
            case doHash("DragonRespawn"): {
                auto Call = RemoteCall::importAs<bool(int64 enderDragonUniqueID)>(eventName, eventId);
                eventBus->emplaceListener<Event::EntityEvent::DragonRespawnBeforeEvent>(
                    [Call](Event::EntityEvent::DragonRespawnBeforeEvent& ev) {
                        bool result = true;
                        try {
                            result = Call(ev.getEnderDragon().id);
                        } catch (...) {}
                        if (!result) {
                            ev.cancel();
                        }
                    }
                );
                return true;
            }
            case doHash("ProjectileTryCreate"): {
                auto Call = RemoteCall::importAs<bool(Actor * mob, int64 uniqueId)>(eventName, eventId);
                eventBus->emplaceListener<Event::EntityEvent::ProjectileCreateBeforeEvent>(
                    [Call](Event::EntityEvent::ProjectileCreateBeforeEvent& ev) {
                        bool result = true;
                        try {
                            auto uid = ev.getShooter() ? ev.getShooter()->getOrCreateUniqueID().id : -1;
                            result   = Call(&ev.self(), uid);
                        } catch (...) {}
                        if (!result) {
                            ev.cancel();
                        }
                    }
                );
                return true;
            }
            case doHash("ProjectileCreate"): {
                auto Call = RemoteCall::importAs<bool(Actor * mob, int64 uniqueId)>(eventName, eventId);
                eventBus->emplaceListener<Event::EntityEvent::ProjectileCreateAfterEvent>(
                    [Call](Event::EntityEvent::ProjectileCreateAfterEvent& ev) {
                        try {
                            auto uid = ev.getShooter() ? ev.getShooter()->getOrCreateUniqueID().id : -1;
                            Call(&ev.self(), uid);
                        } catch (...) {}
                    }
                );
                return true;
            }
            case doHash("SpawnWanderingTrader"): {
                auto Call = RemoteCall::importAs<bool(std::pair<BlockPos, int> pos)>(eventName, eventId);
                eventBus->emplaceListener<Event::EntityEvent::SpawnWanderingTraderBeforeEvent>(
                    [Call](Event::EntityEvent::SpawnWanderingTraderBeforeEvent& ev) {
                        bool result = true;
                        try {
                            result = Call({ev.getPos(), ev.getRegion().getDimensionId()});
                        } catch (...) {}
                        if (!result) {
                            ev.cancel();
                        }
                    }
                );
                return true;
            }
            case doHash("HandleRequestAction"): {
                auto Call = RemoteCall::importAs<
                    bool(Player * player, std::string const& actionType, std::string const& ContainerNetId, int slot)>(
                    eventName,
                    eventId
                );
                eventBus->emplaceListener<Event::PlayerEvent::HandleRequestActionBeforeEvent>(
                    [Call](Event::PlayerEvent::HandleRequestActionBeforeEvent& ev) {
                        bool result = true;
                        try {
                            auto requestAction = (ItemStackRequestActionTransferBase*)&ev.getRequestAction();
                            result             = Call(
                                &ev.self(),
                                magic_enum::enum_name(requestAction->mActionType).data(),
                                magic_enum::enum_name(requestAction->getSrc().mOpenContainerNetId).data(),
                                requestAction->getSrc().mSlot
                            );
                        } catch (...) {}
                        if (!result) {
                            ev.cancel();
                        }
                    }
                );
                return true;
            }
            default:
                return false;
            }
        }
    );
}