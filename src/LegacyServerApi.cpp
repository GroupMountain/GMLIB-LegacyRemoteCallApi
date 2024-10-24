#include "Global.h"

void Export_Legacy_GMLib_ServerAPI() {
    RemoteCall::exportAs("GMLib_ServerAPI", "setEducationFeatureEnabled", []() -> void {
        gmlib::world::Level::tryEnableEducationEdition();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "registerAbilityCommand", []() -> void {
        gmlib::world::Level::tryRegisterAbilityCommand();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setEnableAchievement", []() -> void {
        gmlib::world::Level::setForceAchievementsEnabled();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setForceTrustSkins", []() -> void {
        gmlib::world::Level::trustAllSkins();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "enableCoResourcePack", []() -> void {
        gmlib::world::Level::requireServerResourcePackAndAllowClientResourcePack();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "getLevelName", []() -> std::string {
        return gmlib::world::Level::getInstance()
            .transform([](gmlib::world::Level& level) -> std::string { return level.getLevelName(); })
            .value_or("");
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setLevelName", [](std::string const& name) -> void {
        if (auto level = gmlib::world::Level::getInstance()) {
            level->setLevelName(name);
        }
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "getLevelSeed", []() -> std::string {
        return gmlib::world::Level::getInstance()
            .transform([](gmlib::world::Level& level) -> std::string { return std::to_string(level.getSeed()); })
            .value_or("");
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setFakeSeed", [](int64_t seed) -> void {
        return gmlib::world::Level::setFakeSeed(seed);
    });
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "spawnEntity",
        [](std::pair<Vec3, int> pos, std::string const& name) -> Actor* {
            return gmlib::world::Spawner::spawnEntity(pos.first, pos.second, name).as_ptr();
        }
    );
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "shootProjectile",
        [](Actor* owner, std::string const& name, float speed, float offset) -> Actor* {
            auto ac = (gmlib::world::Actor*)owner;
            return ac->shootProjectile(name, speed, offset).as_ptr();
        }
    );
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "throwEntity",
        [](Actor* owner, Actor* actor, float speed, float offset) -> bool {
            auto ac = (gmlib::world::Actor*)owner;
            return ac->throwEntity(*actor, speed, offset);
        }
    );
    RemoteCall::exportAs("GMLib_ServerAPI", "PlayerToEntity", [](Player* player) -> Actor* { return (Actor*)player; });
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "addFakeList",
        [](const std::string& name, const std::string& xuid) -> bool {
            return gmlib::tools::FakeList::addFakeList(name, xuid, ActorUniqueID(-1));
        }
    );
    RemoteCall::exportAs("GMLib_ServerAPI", "removeFakeList", [](const std::string& nameOrXuid) -> bool {
        return gmlib::tools::FakeList::removeFakeList(nameOrXuid);
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "removeAllFakeList", []() -> void {
        return gmlib::tools::FakeList::removeAllFakeLists();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "getMaxPlayers", []() -> int {
        return gmlib::world::Level::getInstance()
            .transform([](gmlib::world::Level& level) -> int { return level.getMaxPlayerCount(); })
            .value_or(0);
    });
}
