#include "Global.h"

void Export_Legacy_GMLib_ServerAPI() {
    RemoteCall::exportAs("GMLib_ServerAPI", "setEducationFeatureEnabled", []() -> void {
        GMLIB_Level::addEducationEditionRequired();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "registerAbilityCommand", []() -> void {
        GMLIB_Level::forceEnableAbilityCommand();
    });
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "addFloatingTextPacket",
        [](std::string text, std::pair<Vec3, int> pos, int dimid) -> int {
            if (!isServerStarted) {
                return -1;
            }
            auto ft = new GMLIB::Server::FloatingText(text, pos.first, pos.second);
            return ft->getRuntimeID();
        }
    );
    RemoteCall::exportAs("GMLib_ServerAPI", "deleteFloatingTextPacket", [](int id) -> void {
        if (!isServerStarted) {
            return;
        }
        GMLIB::Server::FloatingText::deleteFloatingText(id);
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setEnableAchievement", []() -> void {
        GMLIB_Level::setForceAchievementsEnabled();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setForceTrustSkins", []() -> void { GMLIB_Level::setForceTrustSkin(); });
    RemoteCall::exportAs("GMLib_ServerAPI", "enableCoResourcePack", []() -> void { GMLIB_Level::setCoResourcePack(); });
    RemoteCall::exportAs("GMLib_ServerAPI", "getLevelName", []() -> std::string {
        if (!isServerStarted) {
            return "";
        }
        return GMLIB_Level::getLevel()->getLevelName();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setLevelName", [](std::string name) -> void {
        if (!isServerStarted) {
            return;
        }
        GMLIB_Level::getLevel()->setLevelName(name);
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setFakeSeed", [](int64_t seed) -> void {
        if (!isServerStarted) {
            return;
        }
        GMLIB_Level::getLevel()->setFakeSeed(seed);
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "spawnEntity", [](std::pair<Vec3, int> pos, std::string name) -> Actor* {
        return GMLIB_Spawner::spawnEntity(pos.first, pos.second, name);
    });
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "shootProjectile",
        [](Actor* owner, std::string name, float speed, float offset) -> Actor* {
            auto ac = (GMLIB_Actor*)owner;
            return ac->shootProjectile(name, speed, offset);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "throwEntity",
        [](Actor* owner, Actor* actor, float speed, float offset) -> bool {
            auto ac = (GMLIB_Actor*)owner;
            return ac->throwEntity(actor, speed, offset);
        }
    );
    RemoteCall::exportAs("GMLib_ServerAPI", "PlayerToEntity", [](Player* player) -> Actor* { return (Actor*)player; });
}