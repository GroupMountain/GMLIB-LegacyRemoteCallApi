#include "Global.h"
using namespace ll::hash_utils;

void Export_Event_API() {
    auto eventBus = &ll::event::EventBus::getInstance();
    RemoteCall::exportAs(
        "GMLIB_API",
        "callCustomEvent",
        [eventBus](std::string eventName, std::string eventId) -> bool {
            if (RemoteCall::hasFunc(eventName, eventId)) {
                switch (do_hash(eventName)) {
                case do_hash("onClientLogin"): {
                    auto Call = RemoteCall::importAs<
                        bool(std::string realName, std::string uuid, std::string serverXuid, std::string clientXuid)>(
                        eventName,
                        eventId
                    );
                    eventBus->emplaceListener<GMLIB::Event::PacketEvent::ClientLoginAfterEvent>(
                        [Call](GMLIB::Event::PacketEvent::ClientLoginAfterEvent& ev) {
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
                case do_hash("onWeatherChange"): {
                    auto Call =
                        RemoteCall::importAs<bool(int lightningLevel, int rainLevel, int lightningLast, int rainLast)>(
                            eventName,
                            eventId
                        );
                    eventBus->emplaceListener<GMLIB::Event::LevelEvent::WeatherUpdateBeforeEvent>(
                        [Call](GMLIB::Event::LevelEvent::WeatherUpdateBeforeEvent& ev) {
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
                case do_hash("onMobPick"): {
                    auto Call = RemoteCall::importAs<bool(Actor * mob, Actor * item)>(eventName, eventId);
                    eventBus->emplaceListener<GMLIB::Event::EntityEvent::MobPickupItemBeforeEvent>(
                        [Call](GMLIB::Event::EntityEvent::MobPickupItemBeforeEvent& ev) {
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
                case do_hash("onItemTrySpawn"): {
                    auto Call = RemoteCall::importAs<
                        bool(const ItemStack* item, std::pair<Vec3, int> position, Actor* spawner)>(eventName, eventId);
                    eventBus->emplaceListener<GMLIB::Event::EntityEvent::ItemActorSpawnBeforeEvent>(
                        [Call](GMLIB::Event::EntityEvent::ItemActorSpawnBeforeEvent& ev) {
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
                case do_hash("onItemSpawned"): {
                    auto Call = RemoteCall::importAs<
                        bool(const ItemStack* item, Actor* itemActor, std::pair<Vec3, int> position, Actor* spawner)>(
                        eventName,
                        eventId
                    );
                    eventBus->emplaceListener<GMLIB::Event::EntityEvent::ItemActorSpawnAfterEvent>(
                        [Call](GMLIB::Event::EntityEvent::ItemActorSpawnAfterEvent& ev) {
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
                case do_hash("onTextSend"): {
                    auto Call = RemoteCall::importAs<bool(std::string author, std::string message)>(eventName, eventId);
                    eventBus->emplaceListener<GMLIB::Event::PacketEvent::TextPacketSendBeforeEvent>(
                        [Call](GMLIB::Event::PacketEvent::TextPacketSendBeforeEvent& ev) {
                            auto pkt    = ev.getPacket();
                            bool result = true;
                            try {
                                result = Call(pkt.mAuthor, pkt.mMessage);
                            } catch (...) {}
                            if (!result) {
                                ev.cancel();
                            }
                        }
                    );
                    return true;
                }
                case do_hash("onLeaveBed"): {
                    auto Call = RemoteCall::importAs<bool(Player * pl)>(eventName, eventId);
                    eventBus->emplaceListener<GMLIB::Event::PlayerEvent::PlayerStopSleepBeforeEvent>(
                        [Call](GMLIB::Event::PlayerEvent::PlayerStopSleepBeforeEvent& ev) {
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
                case do_hash("onDeathMessage"): {
                    auto Call = RemoteCall::importAs<bool(std::string message, std::vector<std::string>, Actor * dead)>(
                        eventName,
                        eventId
                    );
                    eventBus->emplaceListener<GMLIB::Event::EntityEvent::DeathMessageAfterEvent>(
                        [Call](GMLIB::Event::EntityEvent::DeathMessageAfterEvent& ev) {
                            auto msg    = ev.getDeathMessage();
                            auto source = ev.getDamageSource();
                            try {
                                Call(msg.first, msg.second, &ev.self());
                            } catch (...) {}
                        }
                    );
                    return true;
                }
                default:
                    return false;
                }
            }
            return false;
        }
    );
}