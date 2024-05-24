#include "GMLIB/Server/FakeListAPI.h"
#include "Global.h"
#include "mc/world/ActorUniqueID.h"

void Export_Legacy_GMLib_ServerAPI() {
    RemoteCall::exportAs("GMLib_ServerAPI", "setEducationFeatureEnabled", []() -> void {
        GMLIB_Level::tryEnableEducationEdition();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "registerAbilityCommand", []() -> void {
        GMLIB_Level::tryRegisterAbilityCommand();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setEnableAchievement", []() -> void {
        GMLIB_Level::setForceAchievementsEnabled();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setForceTrustSkins", []() -> void { GMLIB_Level::trustAllSkins(); });
    RemoteCall::exportAs("GMLib_ServerAPI", "enableCoResourcePack", []() -> void {
        GMLIB_Level::requireServerResourcePackAndAllowClientResourcePack();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "getLevelName", []() -> std::string {
        auto level = GMLIB_Level::getInstance();
        if (!level) {
            return "";
        }
        return level->getLevelName();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setLevelName", [](std::string const& name) -> void {
        auto level = GMLIB_Level::getInstance();
        if (!level) {
            return;
        }
        return level->setLevelName(name);
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setFakeSeed", [](int64_t seed) -> void {
        return GMLIB_Level::setFakeSeed(seed);
    });
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "spawnEntity",
        [](std::pair<Vec3, int> pos, std::string const& name) -> Actor* {
            return GMLIB_Spawner::spawnEntity(pos.first, pos.second, name);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "shootProjectile",
        [](Actor* owner, std::string const& name, float speed, float offset) -> Actor* {
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
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "addFakeList",
        [](const std::string& name, const std::string& xuid) -> bool {
            return GMLIB::Server::FakeList::addFakeList(name, xuid, ActorUniqueID(-1));
        }
    );
    RemoteCall::exportAs("GMLib_ServerAPI", "removeFakeList", [](const std::string& nameOrXuid) -> bool {
        return GMLIB::Server::FakeList::removeFakeList(nameOrXuid);
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "removeAllFakeList", []() -> void {
        return GMLIB::Server::FakeList::removeAllFakeLists();
    });
}
