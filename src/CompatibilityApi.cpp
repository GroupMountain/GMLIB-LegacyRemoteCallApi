#include "Global.h"
#include <regex>

bool isInteger(const std::string& str) {
    std::regex pattern("^[+-]?\\d+$");
    return std::regex_match(str, pattern);
}

ActorUniqueID parseScriptUniqueID(std::string uniqueId) {
    if (!isInteger(uniqueId)) {
        return ActorUniqueID::INVALID_ID;
    }
    return ActorUniqueID(std::stoll(uniqueId));
}

void Export_Compatibility_API() {
    RemoteCall::exportAs("GMLIB_API", "unregisterRecipe", [](std::string id) -> bool {
        auto level = GMLIB_Level::getInstance();
        if (!level) {
            return false;
        }
        return GMLIB::Mod::CustomRecipe::unregisterRecipe(id);
    });
    RemoteCall::exportAs("GMLIB_API", "setCustomPackPath", [](std::string path) -> void {
        GMLIB::Mod::CustomPacks::addCustomPackPath(path);
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
    RemoteCall::exportAs("GMLIB_API", "getPlayerNbt", [](std::string uuid) -> std::unique_ptr<CompoundTag> {
        auto uid = mce::UUID::fromString(uuid);
        return std::move(GMLIB_Player::getPlayerNbt(uid));
    });
    RemoteCall::exportAs("GMLIB_API", "setPlayerNbt", [](std::string uuid, CompoundTag* nbt, bool forceCreate) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        return GMLIB_Player::setPlayerNbt(uid, *nbt, forceCreate);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerNbtTags",
        [](std::string uuid, CompoundTag* nbt, std::vector<std::string> tags) -> bool {
            auto uid = mce::UUID::fromString(uuid);
            return GMLIB_Player::setPlayerNbtTags(uid, *nbt, tags);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "deletePlayerNbt", [](std::string uuid) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        return GMLIB_Player::deletePlayerNbt(uid);
    });
    RemoteCall::exportAs("GMLIB_API", "getAllExperiments", []() -> std::vector<int> {
        auto             map = GMLIB_Level::getAllExperiments();
        std::vector<int> result;
        for (auto& key : map) {
            result.push_back(key.first);
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
        [](std::pair<Vec3, int> pos, std::string text, bool papi) -> int {
            auto ft = new GMLIB::Server::StaticFloatingText(text, pos.first, pos.second, papi);
            return ft->getRuntimeID();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "setFloatingTextData", [](int id, std::string text) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->setText(text);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "deleteFloatingText", [](int id) -> bool {
        return GMLIB::Server::FloatingText::deleteFloatingText(id);
    });
    RemoteCall::exportAs("GMLIB_API", "sendFloatingTextToPlayer", [](int id, Player* pl) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->sendToClient(*pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "sendFloatingText", [](int id) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->sendToAllClients();
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "removeFloatingTextFromPlayer", [](int id, Player* pl) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->removeFromClient(*pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "removeFloatingText", [](int id) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->removeFromAllClients();
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "updateClientFloatingTextData", [](int id, Player* pl) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->updateClient(*pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "updateAllClientsFloatingTextData", [](int id) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->updateAllClients();
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "isVersionMatched", [](int a, int b, int c) -> bool {
        auto version = GMLIB::Version(a, b, c, "", "");
        return LIB_VERSION >= version;
    });
    RemoteCall::exportAs("GMLIB_API", "getVersion_LRCA", []() -> std::string { return LIB_VERSION.asString(); });
    RemoteCall::exportAs("GMLIB_API", "getVersion_GMLIB", []() -> std::string {
        return GMLIB::Version::getLibVersionString();
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "resourcePackDefaultTranslate",
        [](std::string key, std::vector<std::string> params) -> std::string { return I18nAPI::get(key, params); }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "resourcePackTranslate",
        [](std::string key, std::vector<std::string> params, std::string code) -> std::string {
            return I18nAPI::get(key, params, code);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "chooseResourcePackI18nLanguage", [](std::string code) -> void {
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
    RemoteCall::exportAs("GMLIB_API", "loadLanguage", [](std::string code, std::string lang) -> void {
        if (GMLIB_Level::getInstance()) {
            I18nAPI::loadLanguage(code, lang);
        }
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "updateOrCreateLanguageFile",
        [](std::string code, std::string lang, std::string path) -> void {
            if (GMLIB_Level::getInstance()) {
                I18nAPI::updateOrCreateLanguageFile(path, code, lang);
            }
        }
    );
    RemoteCall::exportAs("GMLIB_API", "loadLanguagePath", [](std::string path) -> void {
        if (GMLIB_Level::getInstance()) {
            I18nAPI::loadLanguagesFromDirectory(path);
        }
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerPosition", [](std::string uuid) -> std::pair<BlockPos, int> {
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
    RemoteCall::exportAs("GMLIB_API", "setPlayerPosition", [](std::string uuid, std::pair<BlockPos, int> pos) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        return GMLIB_Player::setPlayerPosition(uid, pos.first, pos.second);
    });
    RemoteCall::exportAs("GMLIB_API", "playerHasScore", [](std::string uuid, std::string obj) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        if (auto result = GMLIB_Player::getPlayerScore(uid, obj)) {
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerScore", [](std::string uuid, std::string obj) -> int {
        auto uid = mce::UUID::fromString(uuid);
        if (auto result = GMLIB_Player::getPlayerScore(uid, obj)) {
            return result.value();
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "addPlayerScore", [](std::string uuid, std::string obj, int value) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        if (auto res = GMLIB_Player::setPlayerScore(uid, obj, value, PlayerScoreSetFunction::Add)) {
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "reducePlayerScore", [](std::string uuid, std::string obj, int value) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        if (auto res = GMLIB_Player::setPlayerScore(uid, obj, value, PlayerScoreSetFunction::Subtract)) {
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "setPlayerScore", [](std::string uuid, std::string obj, int value) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        if (auto res = GMLIB_Player::setPlayerScore(uid, obj, value)) {
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "resetPlayerScore", [](std::string uuid, std::string obj) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        return GMLIB_Player::resetPlayerScore(uid, obj);
    });
    RemoteCall::exportAs("GMLIB_API", "resetPlayerScores", [](std::string uuid) -> bool {
        auto uid = mce::UUID::fromString(uuid);
        return GMLIB_Player::resetPlayerScore(uid);
    });
    RemoteCall::exportAs("GMLIB_API", "entityHasScore", [](std::string uniqueId, std::string obj) -> bool {
        auto auid = parseScriptUniqueID(uniqueId);
        if (auto result = GMLIB_Scoreboard::getInstance()->getScore(obj, auid)) {
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityScore", [](std::string uniqueId, std::string obj) -> int {
        auto auid = parseScriptUniqueID(uniqueId);
        if (auto result = GMLIB_Scoreboard::getInstance()->getScore(obj, auid)) {
            return result.value();
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "addEntityScore", [](std::string uniqueId, std::string obj, int value) -> bool {
        auto auid = parseScriptUniqueID(uniqueId);
        if (auto res = GMLIB_Scoreboard::getInstance()->setScore(obj, auid, value, PlayerScoreSetFunction::Add)) {
            return true;
        }
        return false;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "reduceEntityScore",
        [](std::string uniqueId, std::string obj, int value) -> bool {
            auto auid = parseScriptUniqueID(uniqueId);
            if (auto res =
                    GMLIB_Scoreboard::getInstance()->setScore(obj, auid, value, PlayerScoreSetFunction::Subtract)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "setEntityScore", [](std::string uniqueId, std::string obj, int value) -> bool {
        auto auid = parseScriptUniqueID(uniqueId);
        if (auto res = GMLIB_Scoreboard::getInstance()->setScore(obj, auid, value)) {
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "resetEntityScore", [](std::string uniqueId, std::string obj) -> bool {
        auto auid = parseScriptUniqueID(uniqueId);
        return GMLIB_Scoreboard::getInstance()->resetScore(obj, auid);
    });
    RemoteCall::exportAs("GMLIB_API", "resetEntityScores", [](std::string uniqueId) -> bool {
        auto auid = parseScriptUniqueID(uniqueId);
        return GMLIB_Scoreboard::getInstance()->resetScore(auid);
    });
    RemoteCall::exportAs("GMLIB_API", "fakePlayerHasScore", [](std::string name, std::string obj) -> bool {
        if (auto result = GMLIB_Scoreboard::getInstance()->getScore(obj, name)) {
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "getFakePlayerScore", [](std::string name, std::string obj) -> int {
        if (auto result = GMLIB_Scoreboard::getInstance()->getScore(obj, name)) {
            return result.value();
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "addFakePlayerScore", [](std::string name, std::string obj, int value) -> bool {
        if (auto res = GMLIB_Scoreboard::getInstance()->setScore(obj, name, value, PlayerScoreSetFunction::Add)) {
            return true;
        }
        return false;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "reduceFakePlayerScore",
        [](std::string name, std::string obj, int value) -> bool {
            if (auto res =
                    GMLIB_Scoreboard::getInstance()->setScore(obj, name, value, PlayerScoreSetFunction::Subtract)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "setFakePlayerScore", [](std::string name, std::string obj, int value) -> bool {
        if (auto res = GMLIB_Scoreboard::getInstance()->setScore(obj, name, value)) {
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "resetFakePlayerScore", [](std::string name, std::string obj) -> bool {
        return GMLIB_Scoreboard::getInstance()->resetScore(obj, name);
    });
    RemoteCall::exportAs("GMLIB_API", "resetFakePlayerScores", [](std::string name) -> bool {
        return GMLIB_Scoreboard::getInstance()->resetScore(name);
    });
    RemoteCall::exportAs("GMLIB_API", "addObjective", [](std::string obj) -> bool {
        if (auto res = GMLIB_Scoreboard::getInstance()->addObjective(obj)) {
            return true;
        }
        return false;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "addObjectiveWithDisplayName",
        [](std::string obj, std::string displayName) -> bool {
            if (auto res = GMLIB_Scoreboard::getInstance()->addObjective(obj, displayName)) {
                return true;
            }
            return false;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getDisplayName", [](std::string obj) -> std::string {
        if (auto result = GMLIB_Scoreboard::getInstance()->getObjectiveDisplayName(obj)) {
            return result.value();
        }
        return "";
    });
    RemoteCall::exportAs("GMLIB_API", "setDisplayName", [](std::string obj, std::string displayName) -> bool {
        return GMLIB_Scoreboard::getInstance()->setObjectiveDisplayName(obj, displayName);
    });
    RemoteCall::exportAs("GMLIB_API", "removeObjective", [](std::string obj) -> bool {
        return GMLIB_Scoreboard::getInstance()->removeObjective(obj);
    });
    RemoteCall::exportAs("GMLIB_API", "setDisplayObjective", [](std::string obj, std::string slot, int order) -> void {
        return GMLIB_Scoreboard::getInstance()->setObjectiveDisplay(obj, slot, (ObjectiveSortOrder)order);
    });
    RemoteCall::exportAs("GMLIB_API", "clearDisplayObjective", [](std::string slot) -> void {
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
    RemoteCall::exportAs("GMLIB_API", "getPlayerFromUuid", [](std::string uuid) -> Player* {
        auto uid = mce::UUID::fromString(uuid);
        return ll::service::getLevel()->getPlayer(uuid);
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerFromUniqueId", [](std::string uniqueId) -> Actor* {
        auto auid = parseScriptUniqueID(uniqueId);
        return ll::service::getLevel()->getPlayer(auid);
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityFromUniqueId", [](std::string uniqueId) -> Actor* {
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
    RemoteCall::exportAs("GMLIB_API", "mergePatchJson", [](std::string oldJson, std::string patchJson) -> std::string {
        auto oldData = nlohmann::ordered_json::parse(oldJson);
        auto newData = nlohmann::ordered_json::parse(patchJson);
        oldData.merge_patch(newData);
        return oldData.dump();
    });
    RemoteCall::exportAs("GMLIB_API", "getXuidByUuid", [](std::string uuid) -> std::string {
        auto uid    = mce::UUID::fromString(uuid);
        auto result = GMLIB::UserCache::getXuidByUuid(uid);
        return result ? result.value() : "";
    });
    RemoteCall::exportAs("GMLIB_API", "getNameByUuid", [](std::string uuid) -> std::string {
        auto uid    = mce::UUID::fromString(uuid);
        auto result = GMLIB::UserCache::getNameByUuid(uid);
        return result ? result.value() : "";
    });
    RemoteCall::exportAs("GMLIB_API", "getUuidByXuid", [](std::string xuid) -> std::string {
        auto result = GMLIB::UserCache::getUuidByXuid(xuid);
        return result ? result.value().asString() : "";
    });
    RemoteCall::exportAs("GMLIB_API", "getNameByXuid", [](std::string xuid) -> std::string {
        auto result = GMLIB::UserCache::getNameByXuid(xuid);
        return result ? result.value() : "";
    });
    RemoteCall::exportAs("GMLIB_API", "getXuidByName", [](std::string name) -> std::string {
        auto result = GMLIB::UserCache::getXuidByName(name);
        return result ? result.value() : "";
    });
    RemoteCall::exportAs("GMLIB_API", "getUuidByName", [](std::string name) -> std::string {
        auto result = GMLIB::UserCache::getUuidByName(name);
        return result ? result.value().asString() : "";
    });
    RemoteCall::exportAs("GMLIB_API", "getUuidByName", [](std::string name) -> std::string {
        auto result = GMLIB::UserCache::getUuidByName(name);
        return result ? result.value().asString() : "";
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "getAllPlayerInfo",
        []() -> std::vector<std::unordered_map<std::string, std::string>> {
            std::vector<std::unordered_map<std::string, std::string>> result;
            GMLIB::UserCache::forEach([&result](const GMLIB::UserCache::UserCacheEntry& entry) {
                std::unordered_map<std::string, std::string> info;
                info["Name"] = entry.mName;
                info["Xuid"] = entry.mXuid;
                info["Uuid"] = entry.mUuid.asString();
                result.push_back(info);
            });
            return result;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getBlockRuntimeId", [](std::string blockName) -> uint {
        if (auto block = Block::tryGetFromRegistry(blockName)) {
            return block->getRuntimeId();
        }
        return 0;
    });
}