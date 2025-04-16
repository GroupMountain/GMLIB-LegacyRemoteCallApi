#include "Global.h"

void Export_Legacy_GMLib_ServerAPI() {
    RemoteCall::exportAs("GMLib_ServerAPI", "setEducationFeatureEnabled", []() -> void {
        getLogger().error("GMLib_ServerAPI::setEducationFeatureEnabled is not implemented");
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "registerAbilityCommand", []() -> void {
        getLogger().error("GMLib_ServerAPI::registerAbilityCommand is not implemented");
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setEnableAchievement", []() -> void {
        getLogger().error("GMLib_ServerAPI::setEnableAchievement is not implemented");
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setForceTrustSkins", []() -> void {
        getLogger().error("GMLib_ServerAPI::setForceTrustSkins is not implemented");
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "enableCoResourcePack", []() -> void {
        getLogger().error("GMLib_ServerAPI::enableCoResourcePack is not implemented");
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "getLevelName", []() -> std::string {
        return GMLevel::getInstance().transform(
                                         [](GMLevel& level) -> std::string { return level.getLevelName(); }
        ).value_or("");
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setLevelName", [](std::string const& name) -> void {
        if (auto level = GMLevel::getInstance()) {
            level->setLevelName(name);
        }
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "getLevelSeed", []() -> std::string {
        return GMLevel::getInstance()
            .transform([](GMLevel& level) -> std::string { return std::to_string(level.getSeed()); })
            .value_or("");
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "setFakeSeed", [](int64_t seed) -> void {
        getLogger().error("GMLib_ServerAPI::setFakeSeed is not implemented");
    });
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "spawnEntity",
        [](std::pair<Vec3, int> pos, std::string const& name) -> Actor* {
            return GMSpawner::spawnEntity(pos.first, pos.second, name).as_ptr();
        }
    );
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "shootProjectile",
        [](Actor* owner, std::string const& name, float speed, float offset) -> Actor* {
            auto actor = GMSpawner::spawnEntity(owner->getPosition(), owner->getDimensionId(), name);
            if (!actor) return nullptr;
            ((GMActor*)owner)->setProjectile((GMActor&)*actor, speed, offset);
            return actor.as_ptr();
        }
    );
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "throwEntity",
        [](Actor* owner, Actor* actor, float speed, float offset) -> bool {
            auto ac = (GMActor*)owner;
            ac->setProjectile((GMActor&)*actor, speed, offset);
            return true;
        }
    );
    RemoteCall::exportAs("GMLib_ServerAPI", "PlayerToEntity", [](Player* player) -> Actor* { return (Actor*)player; });
    RemoteCall::exportAs(
        "GMLib_ServerAPI",
        "addFakeList",
        [](const std::string& name, const std::string& xuid) -> bool {
            PlayerListAPI::push_back(name, xuid);
            return true;
        }
    );
    RemoteCall::exportAs("GMLib_ServerAPI", "removeFakeList", [](const std::string& nameOrXuid) -> bool {
        PlayerListAPI::resetListName(nameOrXuid);
        return true;
    });
    RemoteCall::exportAs("GMLib_ServerAPI", "removeAllFakeList", []() -> void { PlayerListAPI::clear(); });
    RemoteCall::exportAs("GMLib_ServerAPI", "getMaxPlayers", []() -> int {
        return GMLevel::getInstance().transform(
                                         [](GMLevel& level) -> int { return level.getMaxPlayerCount(); }
        ).value_or(0);
    });
}
