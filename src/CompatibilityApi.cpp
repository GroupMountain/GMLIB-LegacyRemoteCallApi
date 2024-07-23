#include "Global.h"
#include "magic_enum.hpp"
#include "mc/network/packet/InventorySlotPacket.h"
#include "mc/world/Container.h"
#include <map>
#include <regex>
#include <vector>

bool isInteger(const std::string& str) {
    std::regex pattern("^[+-]?\\d+$");
    return std::regex_match(str, pattern);
}

ActorUniqueID parseScriptUniqueID(std::string const& uniqueId) {
    if (!isInteger(uniqueId)) {
        return ActorUniqueID::INVALID_ID;
    }
    return ActorUniqueID(std::stoll(uniqueId));
}

void Export_Compatibility_API() {
    RemoteCall::exportAs("GMLIB_API", "unregisterRecipe", [](std::string const& id) -> bool {
        auto level = GMLIB_Level::getInstance();
        if (!level) {
            return false;
        }
        return CustomRecipe::unregisterRecipe(id);
    });
    RemoteCall::exportAs("GMLIB_API", "setCustomPackPath", [](std::string const& path) -> void {
        CustomPacks::addCustomPackPath(path);
    });
    RemoteCall::exportAs("GMLIB_API", "getServerMspt", []() -> float {
        auto level = GMLIB_Level::getInstance();
        if (!level) {
            return 0.0f;
        }
        return level->getServerMspt();
    });
    RemoteCall::exportAs("GMLIB_API", "getServerCurrentTps", []() -> float {
        auto level = GMLIB_Level::getInstance();
        if (!level) {
            return 0.0f;
        }
        return level->getServerCurrentTps();
    });
    RemoteCall::exportAs("GMLIB_API", "getServerAverageTps", []() -> float {
        auto level = GMLIB_Level::getInstance();
        if (!level) {
            return 0.0f;
        }
        return level->getServerAverageTps();
    });
    RemoteCall::exportAs("GMLIB_API", "getAllPlayerUuids", []() -> std::vector<std::string> {
        std::vector<std::string> result;
        std::vector<mce::UUID>   uuids = GMLIB_Player::getAllUuids();
        for (auto& uuid : uuids) {
            result.push_back(uuid.asString());
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerNbt", [](std::string const& uuid) -> std::unique_ptr<CompoundTag> {
        auto uid = mce::UUID::fromString(uuid);
        return std::move(GMLIB_Player::getPlayerNbt(uid));
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerNbt",
        [](std::string const& uuid, CompoundTag* nbt, bool forceCreate) -> bool {
            auto uid = mce::UUID::fromString(uuid);
            return GMLIB_Player::setPlayerNbt(uid, *nbt, forceCreate);
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerNbtTags",
        [](std::string const& uuid, CompoundTag* nbt, std::vector<std::string> tags) -> bool {
            auto uid = mce::UUID::fromString(uuid);
            return GMLIB_Player::setPlayerNbtTags(uid, *nbt, tags);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "deletePlayerNbt", [](std::string const& uuid) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        return GMLIB_Player::deletePlayerNbt(uid);
    });
    RemoteCall::exportAs("GMLIB_API", "getAllExperiments", []() -> std::vector<int> {
        auto             list = GMLIB_Level::getAllExperiments();
        std::vector<int> result;
        for (auto& key : list) {
            result.push_back((int)key);
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getExperimentTranslateKey", [](int id) -> std::string {
        std::string result;
        try {
            result = Experiments::getExperimentTextID(AllExperiments(id));
        } catch (...) {}
        return result;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "createFloatingText",
        [](std::pair<Vec3, int> pos, std::string const& text, bool papi) -> int {
            auto& manager = FloatingTextManager::getInstance();
            auto  ft      = manager.createStatic(text, pos.first, pos.second, papi);
            manager.add(ft);
            return ft->getRuntimeID();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "setFloatingTextData", [](int id, std::string const& text) -> bool {
        if (auto ft = FloatingTextManager::getInstance().getFloatingText(id)) {
            ft->setText(text);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "deleteFloatingText", [](int id) -> bool {
        return FloatingTextManager::getInstance().remove(id);
    });
    RemoteCall::exportAs("GMLIB_API", "sendFloatingTextToPlayer", [](int id, Player* pl) -> bool {
        if (auto ft = FloatingTextManager::getInstance().getFloatingText(id)) {
            ft->sendTo(*pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "sendFloatingText", [](int id) -> bool {
        if (auto ft = FloatingTextManager::getInstance().getFloatingText(id)) {
            ft->sendToClients();
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "removeFloatingTextFromPlayer", [](int id, Player* pl) -> bool {
        if (auto ft = FloatingTextManager::getInstance().getFloatingText(id)) {
            ft->removeFrom(*pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "removeFloatingText", [](int id) -> bool {
        if (auto ft = FloatingTextManager::getInstance().getFloatingText(id)) {
            ft->removeFromClients();
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "updateClientFloatingTextData", [](int id, Player* pl) -> bool {
        if (auto ft = FloatingTextManager::getInstance().getFloatingText(id)) {
            ft->update(*pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "updateAllClientsFloatingTextData", [](int id) -> bool {
        if (auto ft = FloatingTextManager::getInstance().getFloatingText(id)) {
            ft->updateClients();
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "isVersionMatched", [](int a, int b, int c) -> bool {
        auto version = Version(a, b, c, "", "");
        return LIB_VERSION >= version;
    });
    RemoteCall::exportAs("GMLIB_API", "getVersion_LRCA", []() -> std::string { return LIB_VERSION.asString(); });
    RemoteCall::exportAs("GMLIB_API", "getVersion_GMLIB", []() -> std::string {
        return Version::getLibVersionString();
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "resourcePackDefaultTranslate",
        [](std::string const& key, std::vector<std::string> params) -> std::string { return I18nAPI::get(key, params); }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "resourcePackTranslate",
        [](std::string const& key, std::vector<std::string> params, std::string const& code) -> std::string {
            return I18nAPI::get(key, params, code);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "chooseResourcePackI18nLanguage", [](std::string const& code) -> void {
        if (GMLIB_Level::getInstance()) {
            I18nAPI::chooseLanguage(code);
        }
    });
    RemoteCall::exportAs("GMLIB_API", "getResourcePackI18nLanguage", []() -> std::string {
        if (GMLIB_Level::getInstance()) {
            return I18nAPI::getCurrentLanguageCode();
        }
        return "unknown";
    });
    RemoteCall::exportAs("GMLIB_API", "getSupportedLanguages", []() -> std::vector<std::string> {
        if (GMLIB_Level::getInstance()) {
            return I18nAPI::getSupportedLanguageCodes();
        }
        return {};
    });
    RemoteCall::exportAs("GMLIB_API", "loadLanguage", [](std::string const& code, std::string const& lang) -> void {
        if (GMLIB_Level::getInstance()) {
            I18nAPI::loadLanguage(code, lang);
        }
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "updateOrCreateLanguageFile",
        [](std::string const& code, std::unordered_map<std::string, std::string> lang, std::string const& path
        ) -> void {
            if (GMLIB_Level::getInstance()) {
                I18nAPI::updateOrCreateLanguageFile(path, code, lang);
            }
        }
    );
    RemoteCall::exportAs("GMLIB_API", "loadLanguagePath", [](std::string const& path) -> void {
        if (GMLIB_Level::getInstance()) {
            I18nAPI::loadLanguagesFromDirectory(path);
        }
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerPosition", [](std::string const& uuid) -> std::pair<BlockPos, int> {
        auto uid = mce::UUID::fromString(uuid);
        auto pos = GMLIB_Player::getPlayerPosition(uid);
        if (pos.has_value()) {
            return pos.value();
        }
        return {
            {0, 0, 0},
            -1
        };
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerPosition",
        [](std::string const& uuid, std::pair<BlockPos, int> pos) -> bool {
            auto uid = mce::UUID::fromString(uuid);
            return GMLIB_Player::setPlayerPosition(uid, pos.first, pos.second);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "playerHasScore", [](std::string const& uuid, std::string const& obj) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        if (auto result = GMLIB_Player::getPlayerScore(uid, obj)) {
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerScore", [](std::string const& uuid, std::string const& obj) -> int {
        auto uid = mce::UUID::fromString(uuid);
        if (auto result = GMLIB_Player::getPlayerScore(uid, obj)) {
            return result.value();
        }
        return 0;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "addPlayerScore",
        [](std::string const& uuid, std::string const& obj, int value) -> bool {
            auto uid = mce::UUID::fromString(uuid);
            if (auto res = GMLIB_Player::setPlayerScore(uid, obj, value, PlayerScoreSetFunction::Add)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "reducePlayerScore",
        [](std::string const& uuid, std::string const& obj, int value) -> bool {
            auto uid = mce::UUID::fromString(uuid);
            if (auto res = GMLIB_Player::setPlayerScore(uid, obj, value, PlayerScoreSetFunction::Subtract)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerScore",
        [](std::string const& uuid, std::string const& obj, int value) -> bool {
            auto uid = mce::UUID::fromString(uuid);
            if (auto res = GMLIB_Player::setPlayerScore(uid, obj, value)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "resetPlayerScore", [](std::string const& uuid, std::string const& obj) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        return GMLIB_Player::resetPlayerScore(uid, obj);
    });
    RemoteCall::exportAs("GMLIB_API", "resetPlayerScores", [](std::string const& uuid) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        return GMLIB_Player::resetPlayerScore(uid);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "entityHasScore",
        [](std::string const& uniqueId, std::string const& obj) -> bool {
            auto auid = parseScriptUniqueID(uniqueId);
            if (auto result = GMLIB_Scoreboard::getInstance()->getScore(obj, auid)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getEntityScore", [](std::string const& uniqueId, std::string const& obj) -> int {
        auto auid = parseScriptUniqueID(uniqueId);
        if (auto result = GMLIB_Scoreboard::getInstance()->getScore(obj, auid)) {
            return result.value();
        }
        return 0;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "addEntityScore",
        [](std::string const& uniqueId, std::string const& obj, int value) -> bool {
            auto auid = parseScriptUniqueID(uniqueId);
            if (auto res = GMLIB_Scoreboard::getInstance()->setScore(obj, auid, value, PlayerScoreSetFunction::Add)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "reduceEntityScore",
        [](std::string const& uniqueId, std::string const& obj, int value) -> bool {
            auto auid = parseScriptUniqueID(uniqueId);
            if (auto res =
                    GMLIB_Scoreboard::getInstance()->setScore(obj, auid, value, PlayerScoreSetFunction::Subtract)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "setEntityScore",
        [](std::string const& uniqueId, std::string const& obj, int value) -> bool {
            auto auid = parseScriptUniqueID(uniqueId);
            if (auto res = GMLIB_Scoreboard::getInstance()->setScore(obj, auid, value)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "resetEntityScore",
        [](std::string const& uniqueId, std::string const& obj) -> bool {
            auto auid = parseScriptUniqueID(uniqueId);
            return GMLIB_Scoreboard::getInstance()->resetScore(obj, auid);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "resetEntityScores", [](std::string const& uniqueId) -> bool {
        auto auid = parseScriptUniqueID(uniqueId);
        return GMLIB_Scoreboard::getInstance()->resetScore(auid);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "fakePlayerHasScore",
        [](std::string const& name, std::string const& obj) -> bool {
            if (auto result = GMLIB_Scoreboard::getInstance()->getScore(obj, name)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getFakePlayerScore", [](std::string const& name, std::string const& obj) -> int {
        if (auto result = GMLIB_Scoreboard::getInstance()->getScore(obj, name)) {
            return result.value();
        }
        return 0;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "addFakePlayerScore",
        [](std::string const& name, std::string const& obj, int value) -> bool {
            if (auto res = GMLIB_Scoreboard::getInstance()->setScore(obj, name, value, PlayerScoreSetFunction::Add)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "reduceFakePlayerScore",
        [](std::string const& name, std::string const& obj, int value) -> bool {
            if (auto res =
                    GMLIB_Scoreboard::getInstance()->setScore(obj, name, value, PlayerScoreSetFunction::Subtract)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "setFakePlayerScore",
        [](std::string const& name, std::string const& obj, int value) -> bool {
            if (auto res = GMLIB_Scoreboard::getInstance()->setScore(obj, name, value)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "resetFakePlayerScore",
        [](std::string const& name, std::string const& obj) -> bool {
            return GMLIB_Scoreboard::getInstance()->resetScore(obj, name);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "resetFakePlayerScores", [](std::string const& name) -> bool {
        return GMLIB_Scoreboard::getInstance()->resetScore(name);
    });
    RemoteCall::exportAs("GMLIB_API", "addObjective", [](std::string const& obj) -> bool {
        if (auto res = GMLIB_Scoreboard::getInstance()->addObjective(obj)) {
            return true;
        }
        return false;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "addObjectiveWithDisplayName",
        [](std::string const& obj, std::string const& displayName) -> bool {
            if (auto res = GMLIB_Scoreboard::getInstance()->addObjective(obj, displayName)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getDisplayName", [](std::string const& obj) -> std::string {
        if (auto result = GMLIB_Scoreboard::getInstance()->getObjectiveDisplayName(obj)) {
            return result.value();
        }
        return "";
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setDisplayName",
        [](std::string const& obj, std::string const& displayName) -> bool {
            return GMLIB_Scoreboard::getInstance()->setObjectiveDisplayName(obj, displayName);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "removeObjective", [](std::string const& obj) -> bool {
        return GMLIB_Scoreboard::getInstance()->removeObjective(obj);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setDisplayObjective",
        [](std::string const& obj, std::string const& slot, int order) -> void {
            return GMLIB_Scoreboard::getInstance()->setObjectiveDisplay(obj, slot, (ObjectiveSortOrder)order);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "clearDisplayObjective", [](std::string const& slot) -> void {
        return GMLIB_Scoreboard::getInstance()->clearObjectiveDisplay(slot);
    });
    RemoteCall::exportAs("GMLIB_API", "getAllObjectives", []() -> std::vector<std::string> {
        auto                     objs = GMLIB_Scoreboard::getInstance()->getObjectives();
        std::vector<std::string> result;
        for (auto& obj : objs) {
            result.push_back(obj->getName());
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getAllScoreboardPlayers", []() -> std::vector<std::string> {
        auto                     uuids = GMLIB_Scoreboard::getInstance()->getAllPlayerUuids();
        std::vector<std::string> result;
        for (auto& uuid : uuids) {
            result.push_back(uuid.asString());
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getAllScoreboardFakePlayers", []() -> std::vector<std::string> {
        auto                     names = GMLIB_Scoreboard::getInstance()->getAllFakePlayers();
        std::vector<std::string> result;
        for (auto& name : names) {
            result.push_back(name);
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getAllScoreboardEntities", []() -> std::vector<std::string> {
        auto                     uniqueIds = GMLIB_Scoreboard::getInstance()->getAllEntities();
        std::vector<std::string> result;
        for (auto& uniqueId : uniqueIds) {
            result.push_back(std::to_string(uniqueId.id));
        }
        return result;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "getAllTrackedTargets",
        []() -> std::vector<std::unordered_map<std::string, std::string>> {
            std::vector<std::unordered_map<std::string, std::string>> result;
            auto uuids = GMLIB_Scoreboard::getInstance()->getAllPlayerUuids();
            for (auto& uuid : uuids) {
                std::unordered_map<std::string, std::string> data;
                data["Type"] = "Player";
                data["Uuid"] = uuid.asString();
                result.push_back(data);
            }
            auto names = GMLIB_Scoreboard::getInstance()->getAllFakePlayers();
            for (auto& name : names) {
                std::unordered_map<std::string, std::string> data;
                data["Type"] = "FakePlayer";
                data["Name"] = name;
                result.push_back(data);
            }
            auto uniqueIds = GMLIB_Scoreboard::getInstance()->getAllEntities();
            for (auto& uniqueId : uniqueIds) {
                std::unordered_map<std::string, std::string> data;
                data["Type"]     = "Entity";
                data["UniqueId"] = std::to_string(uniqueId.id);
                result.push_back(data);
            }
            return result;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getPlayerFromUuid", [](std::string const& uuid) -> Player* {
        return ll::service::getLevel()->getPlayer(mce::UUID::fromString(uuid));
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerFromUniqueId", [](std::string const& uniqueId) -> Actor* {
        auto auid = parseScriptUniqueID(uniqueId);
        return ll::service::getLevel()->getPlayer(auid);
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityFromUniqueId", [](std::string const& uniqueId) -> Actor* {
        auto auid = parseScriptUniqueID(uniqueId);
        return ll::service::getLevel()->fetchEntity(auid);
    });
    RemoteCall::exportAs("GMLIB_API", "getWorldSpawn", []() -> std::pair<BlockPos, int> {
        return {GMLIB_Level::getInstance()->getWorldSpawn(), 0};
    });
    RemoteCall::exportAs("GMLIB_API", "setWorldSpawn", [](std::pair<BlockPos, int> pos) -> bool {
        if (pos.second != 0) {
            return false;
        }
        GMLIB_Level::getInstance()->setWorldSpawn(pos.first);
        return true;
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerSpawnPoint", [](Player* pl) -> std::pair<BlockPos, int> {
        auto player = (GMLIB_Player*)pl;
        auto res    = player->getSpawnPoint();
        return {res.first, res.second};
    });
    RemoteCall::exportAs("GMLIB_API", "setPlayerSpawnPoint", [](Player* pl, std::pair<BlockPos, int> pos) -> void {
        auto player = (GMLIB_Player*)pl;
        player->setSpawnPoint(pos.first, pos.second);
    });
    RemoteCall::exportAs("GMLIB_API", "clearPlayerSpawnPoint", [](Player* pl) -> void {
        auto player = (GMLIB_Player*)pl;
        player->clearSpawnPoint();
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "mergePatchJson",
        [](std::string const& oldJson, std::string const& patchJson) -> std::string {
            auto oldData = nlohmann::ordered_json::parse(oldJson);
            auto newData = nlohmann::ordered_json::parse(patchJson);
            oldData.merge_patch(newData);
            return oldData.dump();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getXuidByUuid", [](std::string const& uuid) -> std::string {
        auto uid    = mce::UUID::fromString(uuid);
        auto result = UserCache::getXuidByUuid(uid);
        return result ? result.value() : "";
    });
    RemoteCall::exportAs("GMLIB_API", "getNameByUuid", [](std::string const& uuid) -> std::string {
        auto uid    = mce::UUID::fromString(uuid);
        auto result = UserCache::getNameByUuid(uid);
        return result ? result.value() : "";
    });
    RemoteCall::exportAs("GMLIB_API", "getUuidByXuid", [](std::string const& xuid) -> std::string {
        auto result = UserCache::getUuidByXuid(xuid);
        return result ? result.value().asString() : "";
    });
    RemoteCall::exportAs("GMLIB_API", "getNameByXuid", [](std::string const& xuid) -> std::string {
        auto result = UserCache::getNameByXuid(xuid);
        return result ? result.value() : "";
    });
    RemoteCall::exportAs("GMLIB_API", "getXuidByName", [](std::string const& name) -> std::string {
        auto result = UserCache::getXuidByName(name);
        return result ? result.value() : "";
    });
    RemoteCall::exportAs("GMLIB_API", "getUuidByName", [](std::string const& name) -> std::string {
        auto result = UserCache::getUuidByName(name);
        return result ? result.value().asString() : "";
    });
    RemoteCall::exportAs("GMLIB_API", "getUuidByName", [](std::string const& name) -> std::string {
        auto result = UserCache::getUuidByName(name);
        return result ? result.value().asString() : "";
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "getAllPlayerInfo",
        []() -> std::vector<std::unordered_map<std::string, std::string>> {
            std::vector<std::unordered_map<std::string, std::string>> result;
            UserCache::forEach([&result](const UserCache::UserCacheEntry& entry) {
                std::unordered_map<std::string, std::string> info;
                info["Name"] = entry.mName;
                info["Xuid"] = entry.mXuid;
                info["Uuid"] = entry.mUuid.asString();
                result.push_back(info);
            });
            return result;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getBlockRuntimeId", [](std::string const& blockName, short legacyData) -> uint {
        if (auto block = Block::tryGetFromRegistry(blockName, legacyData)) {
            return block->getRuntimeId();
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "getBlockTranslateKey", [](Block const* block) -> std::string {
        return block->buildDescriptionId();
    });
    RemoteCall::exportAs("GMLIB_API", "getItemTranslateKey", [](ItemStack* item) -> std::string {
        return item->getDescriptionId();
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityTranslateKey", [](Actor* entity) -> std::string {
        return entity->getEntityLocNameString();
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "readNbtFromFile",
        [](std::string const& path, bool isBinary) -> std::unique_ptr<CompoundTag> {
            if (auto nbt = GMLIB_CompoundTag::readFromFile(path, isBinary)) {
                return std::make_unique<CompoundTag>(nbt.value());
            }
            return nullptr;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "saveNbtToFile",
        [](std::string const& path, CompoundTag* nbt, bool isBinary) -> bool {
            return GMLIB_CompoundTag::saveToFile(path, *nbt, isBinary);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getBlockDestroySpeed", [](Block const* block) -> float {
        return block->getDestroySpeed();
    });
    RemoteCall::exportAs("GMLIB_API", "getDestroyBlockSpeed", [](ItemStack const* item, Block const* block) -> float {
        return item->getDestroySpeed(*block);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "playerDestroyBlock",
        [](Block const* block, std::pair<BlockPos, int> pos, Player* player) -> void {
            return block->playerDestroy(*player, pos.first);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "itemCanDestroyBlock", [](ItemStack const* item, Block const* block) -> bool {
        return item->canDestroy(block);
    });
    RemoteCall::exportAs("GMLIB_API", "itemCanDestroyInCreative", [](ItemStack const* item) -> bool {
        if (auto itemDef = item->getItem()) {
            return itemDef->canDestroyInCreative();
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "itemCanDestroySpecial", [](ItemStack const* item, Block const* block) -> bool {
        return item->canDestroySpecial(*block);
    });
    RemoteCall::exportAs("GMLIB_API", "blockCanDropWithAnyTool", [](Block const* block) -> bool {
        return block->canDropWithAnyTool();
    });
    RemoteCall::exportAs("GMLIB_API", "blockIsAlwaysDestroyable", [](Block const* block) -> bool {
        return block->getMaterial().isAlwaysDestroyable();
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "blockPlayerWillDestroy",
        [](Block const* block, Player* player, std::pair<BlockPos, int> pos) -> bool {
            return block->playerWillDestroy(*player, pos.first);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "playerAttack", [](Player* player, Actor* entity) -> bool {
        return player->attack(*entity, ActorDamageCause::EntityAttack);
    });
    RemoteCall::exportAs("GMLIB_API", "playerPullInEntity", [](Player* player, Actor* entity) -> bool {
        return player->pullInEntity(*entity);
    });
    RemoteCall::exportAs("GMLIB_API", "getBlockTranslateKeyFromName", [](std::string const& blockName) -> std::string {
        if (auto block = Block::tryGetFromRegistry(blockName)) {
            return block->buildDescriptionId();
        }
        return "tile.unknown.name";
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "getBlockLightEmission",
        [](std::string const& blockName, short legacyData) -> char {
            if (auto block = Block::tryGetFromRegistry(blockName, legacyData)) {
                return (char)block->getLightEmission().value;
            }
            return -1;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "getGameRules",
        []() -> std::vector<std::unordered_map<std::string, std::string>> {
            auto gameRules = ll::service::getLevel()->getGameRules().getRules();
            std::vector<std::unordered_map<std::string, std::string>> result;
            for (auto& gameRule : gameRules) {
                std::unordered_map<std::string, std::string> data;
                data["Name"] = gameRule.getName();
                switch (gameRule.getType()) {
                case GameRule::Type::Bool:
                    data["Type"]  = "Bool";
                    data["Value"] = std::to_string(gameRule.getBool());
                    break;
                case GameRule::Type::Float:
                    data["Type"]  = "Float";
                    data["Value"] = std::to_string(gameRule.getFloat());
                    break;
                case GameRule::Type::Int:
                    data["Type"]  = "Int";
                    data["Value"] = std::to_string(gameRule.getInt());
                    break;
                case GameRule::Type::Invalid:
                    break;
                }
                result.push_back(data);
            }
            return result;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getLegalEnchants", [](ItemStack const* item) -> std::vector<std::string> {
        std::vector<int>         enchants = EnchantUtils::getLegalEnchants(item->getItem());
        std::vector<std::string> result;
        for (auto& enchant : enchants) {
            result.push_back(Enchant::getEnchant((Enchant::Type)enchant)->getStringId());
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getEnchantTypeNameFromId", [](int id) -> std::string {
        if (auto enchant = Enchant::getEnchant((Enchant::Type)id)) {
            return std::string(enchant->getStringId());
        }
        return "";
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "applyEnchant",
        [](ItemStack const* item, std::string const& typeName, int level, bool allowNonVanilla) -> bool {
            return EnchantUtils::applyEnchant(
                *(const_cast<ItemStack*>(item)),
                Enchant::getEnchantTypeFromName(HashedString(typeName)),
                level,
                allowNonVanilla
            );
        }
    );
    RemoteCall::exportAs("GMLIB_API", "removeEnchants", [](ItemStack const* item) -> void {
        EnchantUtils::removeEnchants((ItemStack&)*item);
    });
    RemoteCall::exportAs("GMLIB_API", "hasEnchant", [](ItemStack const* item, std::string const& typeName) -> bool {
        return EnchantUtils::hasEnchant(
            Enchant::getEnchantTypeFromName(HashedString(typeName)),
            *(const_cast<ItemStack*>(item))
        );
    });
    RemoteCall::exportAs("GMLIB_API", "getEnchantLevel", [](ItemStack const* item, std::string const& typeName) -> int {
        return EnchantUtils::getEnchantLevel(
            Enchant::getEnchantTypeFromName(HashedString(typeName)),
            *(const_cast<ItemStack*>(item))
        );
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "getEnchantNameAndLevel",
        [](std::string const& typeName, int level) -> std::string {
            return EnchantUtils::getEnchantNameAndLevel(Enchant::getEnchantTypeFromName(HashedString(typeName)), level);
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "dropPlayerItem",
        [](Player* player, ItemStack const* item, bool randomly) -> bool { return player->drop(*item, randomly); }
    );
    RemoteCall::exportAs("GMLIB_API", "getPlayerRuntimeId", [](Player* player) -> uint64 {
        return player->getRuntimeID().id;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityRuntimeId", [](Actor* entity) -> uint64 {
        return entity->getRuntimeID().id;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityNameTag", [](Actor* entity) -> std::string {
        return entity->getNameTag();
    });
    RemoteCall::exportAs("GMLIB_API", "ItemisUnbreakable", [](ItemStack const* item) -> bool {
        return ((GMLIB_ItemStack*)item)->isUnbreakable();
    });
    RemoteCall::exportAs("GMLIB_API", "setItemUnbreakable", [](ItemStack const* item, bool value) -> void {
        ((GMLIB_ItemStack*)item)->setUnbreakable(value);
    });
    RemoteCall::exportAs("GMLIB_API", "getItemShouldKeepOnDeath", [](ItemStack const* item) -> bool {
        return ((GMLIB_ItemStack*)item)->getShouldKeepOnDeath();
    });
    RemoteCall::exportAs("GMLIB_API", "setItemShouldKeepOnDeath", [](ItemStack const* item, bool value) -> void {
        ((GMLIB_ItemStack*)item)->setShouldKeepOnDeath(value);
    });
    RemoteCall::exportAs("GMLIB_API", "getItemLockMode", [](ItemStack const* item) -> int {
        return (int)((GMLIB_ItemStack*)item)->getItemLockMode();
    });
    RemoteCall::exportAs("GMLIB_API", "setItemLockMode", [](ItemStack const* item, int value) -> void {
        ((GMLIB_ItemStack*)item)->setItemLockMode((ItemLockMode)value);
    });
    RemoteCall::exportAs("GMLIB_API", "getItemRepairCost", [](ItemStack const* item) -> int {
        return item->getBaseRepairCost();
    });
    RemoteCall::exportAs("GMLIB_API", "setItemRepairCost", [](ItemStack const* item, int cost) -> void {
        (*(const_cast<ItemStack*>(item))).setRepairCost(cost);
    });
    RemoteCall::exportAs("GMLIB_API", "getItemCanDestroy", [](ItemStack const* item) -> std::vector<std::string> {
        std::vector<std::string> result = {};
        for (auto& block : ((GMLIB_ItemStack*)item)->getCanDestroy()) {
            result.push_back(block->getTypeName());
        }
        return result;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setItemCanDestroy",
        [](ItemStack const* item, std::vector<std::string> blocks) -> void {
            ((GMLIB_ItemStack*)item)->setCanDestroy(blocks);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getItemCanPlaceOn", [](ItemStack const* item) -> std::vector<std::string> {
        std::vector<std::string> result = {};
        for (auto& block : ((GMLIB_ItemStack*)item)->getCanPlaceOn()) {
            result.push_back(block->getTypeName());
        }
        return result;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setItemCanPlaceOn",
        [](ItemStack const* item, std::vector<std::string> blocks) -> void {
            ((GMLIB_ItemStack*)item)->setCanPlaceOn(blocks);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getPlayerHungry", [](Player* player) -> float {
        return player->getMutableAttribute(Player::HUNGER)->getCurrentValue();
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerArmorCoverPercentage", [](Player* player) -> float {
        return player->getArmorCoverPercentage();
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerArmorValue", [](Player* player) -> int {
        return player->getArmorValue();
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityOwnerUniqueId", [](Actor* entity) -> int64 {
        return entity->getOwnerId().id;
    });
    RemoteCall::exportAs("GMLIB_API", "getItemCategoryName", [](ItemStack const* item) -> std::string {
        return item->getCategoryName();
    });
    RemoteCall::exportAs("GMLIB_API", "getItemCustomName", [](ItemStack const* item) -> std::string {
        return item->getCustomName();
    });
    RemoteCall::exportAs("GMLIB_API", "getItemEffecName", [](ItemStack const* item) -> std::string {
        return item->getEffectName();
    });
    RemoteCall::exportAs("GMLIB_API", "itemIsFood", [](ItemStack const* item) -> bool {
        if (auto itemDef = item->getItem()) {
            return itemDef->isFood();
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "setPlayerUIItem", [](Player* player, int slot, ItemStack const* item) -> void {
        player->setPlayerUIItem((PlayerUISlot)slot, *item);
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerUIItem", [](Player* player, int slot) -> ItemStack* {
        return const_cast<ItemStack*>(&player->getPlayerUIItem((PlayerUISlot)slot));
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "sendInventorySlotPacket",
        [](Player* player, int containerId, int slot, ItemStack* item) -> void {
            InventorySlotPacket((ContainerID)containerId, slot, *item).sendTo(*player);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getContainerType", [](Container* container) -> std::string {
        return magic_enum::enum_name(container->getContainerType()).data();
    });
    RemoteCall::exportAs("GMLIB_API", "hasPlayerNbt", [](std::string const& uuid) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        return GMLIB_Player::getPlayerNbt(uid) ? true : false;
    });
}