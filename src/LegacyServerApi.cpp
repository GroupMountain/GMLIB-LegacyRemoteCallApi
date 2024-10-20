#include "Global.h"

void Export_Legacy_GMLib_ServerAPI() {
    RemoteCall::exportAs("GMLib_ServerAPI", "setEducationFeatureEnabled", []() -> void {
        world::Level::tryEnableEducationEdition();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "registerAbilityCommand", []() -> void {
        world::Level::tryRegisterAbilityCommand();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setEnableAchievement", []() -> void {
        world::Level::setForceAchievementsEnabled();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setForceTrustSkins", []() -> void { world::Level::trustAllSkins(); });
    RemoteCall::exportAs("GMLib_ServerAPI", "enableCoResourcePack", []() -> void {
        world::Level::requireServerResourcePackAndAllowClientResourcePack();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "getLevelName", []() -> std::string {
        if (auto level = world::Level::getInstance()) {
            return level->getLevelName();
        }
        return {};
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setLevelName", [](std::string const& name) -> void {
        if (auto level = world::Level::getInstance()) {
            level->setLevelName(name);
        }
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "getLevelSeed", []() -> std::string {
        if (auto level = world::Level::getInstance()) {
            return std::to_string(level->getSeed());
        }
        return {};
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setFakeSeed", [](int64_t seed) -> void {
        return world::Level::setFakeSeed(seed);
    });
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "spawnEntity",
        [](std::pair<Vec3, int> pos, std::string const& name) -> ::Actor* {
            return world::Spawner::spawnEntity(pos.first, pos.second, name).as_ptr();
        }
    );
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "shootProjectile",
        [](::Actor* owner, std::string const& name, float speed, float offset) -> ::Actor* {
            auto ac = (world::Actor*)owner;
            return ac->shootProjectile(name, speed, offset).as_ptr();
        }
    );
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "throwEntity",
        [](::Actor* owner, ::Actor* actor, float speed, float offset) -> bool {
            auto ac = (world::Actor*)owner;
            return ac->throwEntity(*actor, speed, offset);
        }
    );
    RemoteCall::exportAs("GMLib_ServerAPI", "PlayerToEntity", [](::Player* player) -> ::Actor* {
        return (::Actor*)player;
    });
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "addFakeList",
        [](const std::string& name, const std::string& xuid) -> bool {
            return FakeList::addFakeList(name, xuid, ActorUniqueID(-1));
        }
    );
    RemoteCall::exportAs("GMLib_ServerAPI", "removeFakeList", [](const std::string& nameOrXuid) -> bool {
        return FakeList::removeFakeList(nameOrXuid);
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "removeAllFakeList", []() -> void {
        return FakeList::removeAllFakeLists();
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "getMaxPlayers", []() -> int {
        if (auto level = world::Level::getInstance()) {
            return level->getMaxPlayerCount();
        }
        return {};
    });
}
