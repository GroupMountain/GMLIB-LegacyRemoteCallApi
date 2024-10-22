#include "Global.h"
#include <regex>

bool isInteger(const std::string& str) {
    std::regex pattern("^[+-]?\\d+$");
    return std::regex_match(str, pattern);
}

ActorUniqueID parseScriptUniqueID(std::string const& uniqueId) {
    return isInteger(uniqueId) ? ActorUniqueID(std::stoll(uniqueId)) : ActorUniqueID::INVALID_ID;
}

void Export_Compatibility_API() {
    RemoteCall::exportAs("GMLIB_API", "unregisterRecipe", [](std::string const& id) -> bool {
        return gmlib::world::Level::getInstance().has_value() ? gmlib::mod::recipe::RecipeRegistry::unregisterRecipe(id) : false;
    });
    RemoteCall::exportAs("GMLIB_API", "setCustomPackPath", [](std::string const& path) -> void {
        gmlib::tools::AddonsLoader::addCustomPackPath(path);
    });
    RemoteCall::exportAs("GMLIB_API", "getServerMspt", []() -> double {
        return gmlib::world::Level::getInstance()
            .transform([](gmlib::world::Level& level) -> double { return level.getServerMspt(); })
            .value_or(0.0);
    });
    RemoteCall::exportAs("GMLIB_API", "getServerCurrentTps", []() -> float {
        return gmlib::world::Level::getInstance()
            .transform([](gmlib::world::Level& level) -> float { return level.getServerCurrentTps(); })
            .value_or(0.0);
    });
    RemoteCall::exportAs("GMLIB_API", "getServerAverageTps", []() -> double {
        return gmlib::world::Level::getInstance()
            .transform([](gmlib::world::Level& level) -> double { return level.getServerAverageTps(); })
            .value_or(0.0);
    });
    RemoteCall::exportAs("GMLIB_API", "getAllPlayerUuids", []() -> std::vector<std::string> {
        std::vector<std::string> result;
        for (auto& uuid : gmlib::world::Player::getAllUuids()) {
            result.push_back(uuid.asString());
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerNbt", [](std::string const& uuid) -> std::unique_ptr<CompoundTag> {
        return std::move(gmlib::world::Player::getPlayerNbt(mce::UUID::fromString(uuid)));
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerNbt",
        [](std::string const& uuid, CompoundTag* nbt, bool forceCreate) -> bool {
            return gmlib::world::Player::setPlayerNbt(
                mce::UUID::fromString(uuid),
                (gmlib::world::CompoundTag&)*nbt,
                forceCreate
            );
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerNbtTags",
        [](std::string const& uuid, CompoundTag* nbt, std::vector<std::string> tags) -> bool {
            return gmlib::world::Player::setPlayerNbtTags(
                mce::UUID::fromString(uuid),
                (gmlib::world::CompoundTag&)*nbt,
                tags
            );
        }
    );
    RemoteCall::exportAs("GMLIB_API", "deletePlayerNbt", [](std::string const& uuid) -> bool {
        return gmlib::world::Player::deletePlayerNbt(mce::UUID::fromString(uuid));
    });
    RemoteCall::exportAs("GMLIB_API", "getAllExperiments", []() -> std::vector<int> {
        std::vector<int> result;
        for (auto& key : gmlib::world::Level::getAllExperiments()) {
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
            auto ft = gmlib::tools::FloatingTextManager::createStatic(text, pos.first, pos.second, papi);
            gmlib::tools::FloatingTextManager::getInstance().add(ft);
            return ft->getRuntimeID();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "setFloatingTextData", [](int id, std::string const& text) -> bool {
        return gmlib::tools::FloatingTextManager::getInstance()
            .getFloatingText(id)
            .transform([&text](gmlib::tools::FloatingTextBase& ft) -> bool {
                ft.setText(text);
                return true;
            })
            .has_value();
    });
    RemoteCall::exportAs("GMLIB_API", "deleteFloatingText", [](int id) -> bool {
        return gmlib::tools::FloatingTextManager::getInstance().remove(id);
    });
    RemoteCall::exportAs("GMLIB_API", "sendFloatingTextToPlayer", [](int id, Player* pl) -> bool {
        return gmlib::tools::FloatingTextManager::getInstance()
            .getFloatingText(id)
            .transform([&pl](gmlib::tools::FloatingTextBase& ft) -> bool {
                ft.sendTo(*pl);
                return true;
            })
            .has_value();
    });
    RemoteCall::exportAs("GMLIB_API", "sendFloatingText", [](int id) -> bool {
        return gmlib::tools::FloatingTextManager::getInstance()
            .getFloatingText(id)
            .transform([](gmlib::tools::FloatingTextBase& ft) -> bool {
                ft.sendToClients();
                return true;
            })
            .has_value();
    });
    RemoteCall::exportAs("GMLIB_API", "removeFloatingTextFromPlayer", [](int id, Player* pl) -> bool {
        return gmlib::tools::FloatingTextManager::getInstance()
            .getFloatingText(id)
            .transform([&pl](gmlib::tools::FloatingTextBase& ft) -> bool {
                ft.removeFrom(*pl);
                return true;
            })
            .has_value();
    });
    RemoteCall::exportAs("GMLIB_API", "removeFloatingText", [](int id) -> bool {
        return gmlib::tools::FloatingTextManager::getInstance()
            .getFloatingText(id)
            .transform([](gmlib::tools::FloatingTextBase& ft) -> bool {
                ft.removeFromClients();
                return true;
            })
            .has_value();
    });
    RemoteCall::exportAs("GMLIB_API", "updateClientFloatingTextData", [](int id, Player* pl) -> bool {
        return gmlib::tools::FloatingTextManager::getInstance()
            .getFloatingText(id)
            .transform([&pl](gmlib::tools::FloatingTextBase& ft) -> bool {
                ft.update(*pl);
                return true;
            })
            .has_value();
    });
    RemoteCall::exportAs("GMLIB_API", "updateAllClientsFloatingTextData", [](int id) -> bool {
        return gmlib::tools::FloatingTextManager::getInstance()
            .getFloatingText(id)
            .transform([](gmlib::tools::FloatingTextBase& ft) -> bool {
                ft.updateClients();
                return true;
            })
            .has_value();
    });
    RemoteCall::exportAs("GMLIB_API", "isVersionMatched", [](int a, int b, int c) -> bool {
        return LIB_VERSION >= gmlib::Version(a, b, c, "", "");
    });
    RemoteCall::exportAs("GMLIB_API", "getVersion_LRCA", []() -> std::string { return LIB_VERSION.asString(); });
    RemoteCall::exportAs("GMLIB_API", "getVersion_GMLIB", []() -> std::string {
        return gmlib::Version::getLibVersionString();
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "resourcePackDefaultTranslate",
        [](std::string const& key, std::vector<std::string> params) -> std::string {
            return gmlib::world::I18nAPI::get(key, params);
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "resourcePackTranslate",
        [](std::string const& key, std::vector<std::string> params, std::string const& code) -> std::string {
            return gmlib::world::I18nAPI::get(key, params, code);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "chooseResourcePackI18nLanguage", [](std::string const& code) -> void {
        if (gmlib::world::Level::getInstance()) {
            gmlib::world::I18nAPI::chooseLanguage(code);
        }
    });
    RemoteCall::exportAs("GMLIB_API", "getResourcePackI18nLanguage", []() -> std::string {
        return gmlib::world::Level::getInstance().has_value() ? gmlib::world::I18nAPI::getCurrentLanguageCode() : "unknown";
    });
    RemoteCall::exportAs("GMLIB_API", "getSupportedLanguages", []() -> std::vector<std::string> {
        return gmlib::world::Level::getInstance() ? gmlib::world::I18nAPI::getSupportedLanguageCodes()
                                                  : std::vector<std::string>();
    });
    RemoteCall::exportAs("GMLIB_API", "loadLanguage", [](std::string const& code, std::string const& lang) -> void {
        if (gmlib::world::Level::getInstance()) {
            gmlib::world::I18nAPI::loadLanguage(code, lang);
        }
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "updateOrCreateLanguageFile",
        [](std::string const& code, std::unordered_map<std::string, std::string> lang, std::string const& path
        ) -> void {
            if (gmlib::world::Level::getInstance()) {
                gmlib::world::I18nAPI::updateOrCreateLanguageFile(path, code, lang);
            }
        }
    );
    RemoteCall::exportAs("GMLIB_API", "loadLanguagePath", [](std::string const& path) -> void {
        if (gmlib::world::Level::getInstance()) {
            gmlib::world::I18nAPI::loadLanguagesFromDirectory(path);
        }
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerPosition", [](std::string const& uuid) -> std::pair<BlockPos, int> {
        return gmlib::world::Player::getPlayerPosition(mce::UUID::fromString(uuid))
            .value_or(std::pair<BlockPos, int>({0, 0, 0}, -1));
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerPosition",
        [](std::string const& uuid, std::pair<BlockPos, int> pos) -> bool {
            return gmlib::world::Player::setPlayerPosition(mce::UUID::fromString(uuid), pos.first, pos.second);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "playerHasScore", [](std::string const& uuid, std::string const& obj) -> bool {
        return gmlib::world::Player::getPlayerScore(mce::UUID::fromString(uuid), obj).has_value();
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerScore", [](std::string const& uuid, std::string const& obj) -> int {
        return gmlib::world::Player::getPlayerScore(mce::UUID::fromString(uuid), obj).value_or(0);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "addPlayerScore",
        [](std::string const& uuid, std::string const& obj, int value) -> bool {
            return gmlib::world::Player::setPlayerScore(
                       mce::UUID::fromString(uuid),
                       obj,
                       value,
                       PlayerScoreSetFunction::Add
            )
                .has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "reducePlayerScore",
        [](std::string const& uuid, std::string const& obj, int value) -> bool {
            return gmlib::world::Player::setPlayerScore(mce::UUID::fromString(uuid), obj, value, PlayerScoreSetFunction::Subtract).has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerScore",
        [](std::string const& uuid, std::string const& obj, int value) -> bool {
            return gmlib::world::Player::setPlayerScore(mce::UUID::fromString(uuid), obj, value).has_value();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "resetPlayerScore", [](std::string const& uuid, std::string const& obj) -> bool {
        return gmlib::world::Player::resetPlayerScore(mce::UUID::fromString(uuid), obj);
    });
    RemoteCall::exportAs("GMLIB_API", "resetPlayerScores", [](std::string const& uuid) -> bool {
        return gmlib::world::Player::resetPlayerScore(mce::UUID::fromString(uuid));
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "entityHasScore",
        [](std::string const& uniqueId, std::string const& obj) -> bool {
            return gmlib::world::Scoreboard::getInstance()->getScore(obj, parseScriptUniqueID(uniqueId)).has_value();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getEntityScore", [](std::string const& uniqueId, std::string const& obj) -> int {
        return gmlib::world::Scoreboard::getInstance()->getScore(obj, parseScriptUniqueID(uniqueId)).value_or(0);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "addEntityScore",
        [](std::string const& uniqueId, std::string const& obj, int value) -> bool {
            return gmlib::world::Scoreboard::getInstance()
                ->setScore(obj, parseScriptUniqueID(uniqueId), value, PlayerScoreSetFunction::Add)
                .has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "reduceEntityScore",
        [](std::string const& uniqueId, std::string const& obj, int value) -> bool {
            return gmlib::world::Scoreboard::getInstance()
                ->setScore(obj, parseScriptUniqueID(uniqueId), value, PlayerScoreSetFunction::Subtract)
                .has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "setEntityScore",
        [](std::string const& uniqueId, std::string const& obj, int value) -> bool {
            return gmlib::world::Scoreboard::getInstance()->setScore(obj, parseScriptUniqueID(uniqueId), value).has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "resetEntityScore",
        [](std::string const& uniqueId, std::string const& obj) -> bool {
            return gmlib::world::Scoreboard::getInstance()->resetScore(obj, parseScriptUniqueID(uniqueId));
        }
    );
    RemoteCall::exportAs("GMLIB_API", "resetEntityScores", [](std::string const& uniqueId) -> bool {
        return gmlib::world::Scoreboard::getInstance()->resetScore(parseScriptUniqueID(uniqueId));
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "fakePlayerHasScore",
        [](std::string const& name, std::string const& obj) -> bool {
            return gmlib::world::Scoreboard::getInstance()->getScore(obj, name).has_value();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getFakePlayerScore", [](std::string const& name, std::string const& obj) -> int {
        return gmlib::world::Scoreboard::getInstance()->getScore(obj, name).value_or(0);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "addFakePlayerScore",
        [](std::string const& name, std::string const& obj, int value) -> bool {
            return gmlib::world::Scoreboard::getInstance()->setScore(obj, name, value, PlayerScoreSetFunction::Add).has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "reduceFakePlayerScore",
        [](std::string const& name, std::string const& obj, int value) -> bool {
            return gmlib::world::Scoreboard::getInstance()
                ->setScore(obj, name, value, PlayerScoreSetFunction::Subtract)
                .has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "setFakePlayerScore",
        [](std::string const& name, std::string const& obj, int value) -> bool {
            return gmlib::world::Scoreboard::getInstance()->setScore(obj, name, value).has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "resetFakePlayerScore",
        [](std::string const& name, std::string const& obj) -> bool {
            return gmlib::world::Scoreboard::getInstance()->resetScore(obj, name);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "resetFakePlayerScores", [](std::string const& name) -> bool {
        return gmlib::world::Scoreboard::getInstance()->resetScore(name);
    });
    RemoteCall::exportAs("GMLIB_API", "addObjective", [](std::string const& obj) -> bool {
        return gmlib::world::Scoreboard::getInstance()->addObjective(obj).has_value();
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "addObjectiveWithDisplayName",
        [](std::string const& obj, std::string const& displayName) -> bool {
            return gmlib::world::Scoreboard::getInstance()->addObjective(obj, displayName).has_value();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getDisplayName", [](std::string const& obj) -> std::string {
        return gmlib::world::Scoreboard::getInstance()->getObjectiveDisplayName(obj).value_or("");
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setDisplayName",
        [](std::string const& obj, std::string const& displayName) -> bool {
            return gmlib::world::Scoreboard::getInstance()->setObjectiveDisplayName(obj, displayName);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "removeObjective", [](std::string const& obj) -> bool {
        return gmlib::world::Scoreboard::getInstance()->removeObjective(obj);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setDisplayObjective",
        [](std::string const& obj, std::string const& slot, int order) -> void {
            return gmlib::world::Scoreboard::getInstance()->setObjectiveDisplay(obj, slot, (ObjectiveSortOrder)order);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "clearDisplayObjective", [](std::string const& slot) -> void {
        return gmlib::world::Scoreboard::getInstance()->clearObjectiveDisplay(slot);
    });
    RemoteCall::exportAs("GMLIB_API", "getAllObjectives", []() -> std::vector<std::string> {
        std::vector<std::string> result;
        for (auto& obj : gmlib::world::Scoreboard::getInstance()->getObjectives()) {
            result.push_back(obj->getName());
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getAllScoreboardPlayers", []() -> std::vector<std::string> {
        std::vector<std::string> result;
        for (auto& uuid : gmlib::world::Scoreboard::getInstance()->getAllPlayerUuids()) {
            result.push_back(uuid.asString());
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getAllScoreboardFakePlayers", []() -> std::vector<std::string> {
        std::vector<std::string> result;
        for (auto& name : gmlib::world::Scoreboard::getInstance()->getAllFakePlayers()) {
            result.push_back(name);
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getAllScoreboardEntities", []() -> std::vector<std::string> {
        std::vector<std::string> result;
        for (auto& uniqueId : gmlib::world::Scoreboard::getInstance()->getAllEntities()) {
            result.push_back(std::to_string(uniqueId.id));
        }
        return result;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "getAllTrackedTargets",
        []() -> std::vector<std::unordered_map<std::string, std::string>> {
            std::vector<std::unordered_map<std::string, std::string>> result;
            for (auto& uuid : gmlib::world::Scoreboard::getInstance()->getAllPlayerUuids()) {
                result.push_back({
                    {"Type", "Player"       },
                    {"Uuid", uuid.asString()}
                });
            }
            for (auto& name : gmlib::world::Scoreboard::getInstance()->getAllFakePlayers()) {
                result.push_back({
                    {"Type", "FakePlayer"},
                    {"Name", name        }
                });
            }
            for (auto& uniqueId : gmlib::world::Scoreboard::getInstance()->getAllEntities()) {
                result.push_back({
                    {"Type",     "Entity"                   },
                    {"UniqueId", std::to_string(uniqueId.id)}
                });
            }
            return result;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getPlayerFromUuid", [](std::string const& uuid) -> Player* {
        return ll::service::getLevel()->getPlayer(mce::UUID::fromString(uuid));
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerFromUniqueId", [](std::string const& uniqueId) -> Actor* {
        return ll::service::getLevel()->getPlayer(parseScriptUniqueID(uniqueId));
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityFromUniqueId", [](std::string const& uniqueId) -> Actor* {
        return ll::service::getLevel()->fetchEntity(parseScriptUniqueID(uniqueId));
    });
    RemoteCall::exportAs("GMLIB_API", "getWorldSpawn", []() -> std::pair<BlockPos, int> {
        return {gmlib::world::Level::getInstance()->getWorldSpawn(), 0};
    });
    RemoteCall::exportAs("GMLIB_API", "setWorldSpawn", [](std::pair<BlockPos, int> pos) -> bool {
        if (pos.second != 0) return false;
        gmlib::world::Level::getInstance()->setWorldSpawn(pos.first);
        return true;
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerSpawnPoint", [](Player* pl) -> std::pair<BlockPos, int> {
        auto res = ((gmlib::world::Player*)pl)->getSpawnPoint();
        return {res.first, res.second};
    });
    RemoteCall::exportAs("GMLIB_API", "setPlayerSpawnPoint", [](Player* pl, std::pair<BlockPos, int> pos) -> void {
        ((gmlib::world::Player*)pl)->setSpawnPoint(pos.first, pos.second);
    });
    RemoteCall::exportAs("GMLIB_API", "clearPlayerSpawnPoint", [](Player* pl) -> void {
        ((gmlib::world::Player*)pl)->clearSpawnPoint();
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
        return gmlib::tools::UserCache::getXuidByUuid(mce::UUID::fromString(uuid)).value_or("");
    });
    RemoteCall::exportAs("GMLIB_API", "getXuidByName", [](std::string const& name) -> std::string {
        return gmlib::tools::UserCache::getXuidByName(name).value_or("");
    });
    RemoteCall::exportAs("GMLIB_API", "getNameByUuid", [](std::string const& uuid) -> std::string {
        return gmlib::tools::UserCache::getNameByUuid(mce::UUID::fromString(uuid)).value_or("");
    });
    RemoteCall::exportAs("GMLIB_API", "getNameByXuid", [](std::string const& xuid) -> std::string {
        return gmlib::tools::UserCache::getNameByXuid(xuid).value_or("");
    });
    RemoteCall::exportAs("GMLIB_API", "getUuidByXuid", [](std::string const& xuid) -> std::string {
        return gmlib::tools::UserCache::getUuidByXuid(xuid)
            .transform([](mce::UUID&& uuid) -> std::string { return uuid.asString(); })
            .value_or("");
    });
    RemoteCall::exportAs("GMLIB_API", "getUuidByName", [](std::string const& name) -> std::string {
        return gmlib::tools::UserCache::getUuidByName(name)
            .transform([](mce::UUID&& uuid) -> std::string { return uuid.asString(); })
            .value_or("");
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "getAllPlayerInfo",
        []() -> std::vector<std::unordered_map<std::string, std::string>> {
            std::vector<std::unordered_map<std::string, std::string>> result;
            gmlib::tools::UserCache::forEach([&result](const gmlib::tools::UserCache::UserCacheEntry& entry) -> void {
                result.push_back({
                    {"Name", entry.mName           },
                    {"Xuid", entry.mXuid           },
                    {"Uuid", entry.mUuid.asString()}
                });
            });
            return result;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getBlockRuntimeId", [](std::string const& blockName, short legacyData) -> uint {
        return Block::tryGetFromRegistry(blockName, legacyData)
            .transform([](const Block& block) -> uint { return block.getRuntimeId(); })
            .value_or(0);
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
            if (auto nbt = gmlib::world::CompoundTag::readFromFile(path, isBinary)) {
                return std::make_unique<CompoundTag>(nbt.value());
            }
            return nullptr;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "saveNbtToFile",
        [](std::string const& path, CompoundTag* nbt, bool isBinary) -> bool {
            return gmlib::world::CompoundTag::saveToFile(path, *nbt, isBinary);
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
        return Block::tryGetFromRegistry(blockName)
            .transform([](const Block& block) -> std::string { return block.buildDescriptionId(); })
            .value_or("tile.unknown.name");
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "getBlockLightEmission",
        [](std::string const& blockName, short legacyData) -> char {
            return Block::tryGetFromRegistry(blockName)
                .transform([](const Block& block) -> char { return (char)block.getLightEmission().value; })
                .value_or(-1);
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "getGameRules",
        []() -> std::vector<std::unordered_map<std::string, std::string>> {
            std::vector<std::unordered_map<std::string, std::string>> result;
            for (auto& gameRule : ll::service::getLevel()->getGameRules().getRules()) {
                switch (gameRule.getType()) {
                case GameRule::Type::Bool:
                    result.push_back({
                        {"Name",  gameRule.getName()                },
                        {"Type",  "Bool"                            },
                        {"Value", std::to_string(gameRule.getBool())}
                    });
                    break;
                case GameRule::Type::Float:
                    result.push_back({
                        {"Name",  gameRule.getName()                 },
                        {"Type",  "Float"                            },
                        {"Value", std::to_string(gameRule.getFloat())}
                    });
                    break;
                case GameRule::Type::Int:
                    result.push_back({
                        {"Name",  gameRule.getName()               },
                        {"Type",  "Int"                            },
                        {"Value", std::to_string(gameRule.getInt())}
                    });
                    break;
                case GameRule::Type::Invalid:
                    break;
                }
            }
            return result;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getLegalEnchants", [](ItemStack const* item) -> std::vector<std::string> {
        std::vector<std::string> result;
        for (auto& enchant : EnchantUtils::getLegalEnchants(item->getItem())) {
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
        [](ItemStack* item, std::string const& typeName, int level, bool allowNonVanilla) -> bool {
            return EnchantUtils::applyEnchant(
                *item,
                Enchant::getEnchantTypeFromName(HashedString(typeName)),
                level,
                allowNonVanilla
            );
        }
    );
    RemoteCall::exportAs("GMLIB_API", "removeEnchants", [](ItemStack* item) -> void {
        EnchantUtils::removeEnchants(*item);
    });
    RemoteCall::exportAs("GMLIB_API", "hasEnchant", [](ItemStack* item, std::string const& typeName) -> bool {
        return EnchantUtils::hasEnchant(Enchant::getEnchantTypeFromName(HashedString(typeName)), *item);
    });
    RemoteCall::exportAs("GMLIB_API", "getEnchantLevel", [](ItemStack* item, std::string const& typeName) -> int {
        return EnchantUtils::getEnchantLevel(Enchant::getEnchantTypeFromName(HashedString(typeName)), *item);
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
        return ((gmlib::world::ItemStack*)item)->isUnbreakable();
    });
    RemoteCall::exportAs("GMLIB_API", "setItemUnbreakable", [](ItemStack const* item, bool value) -> void {
        ((gmlib::world::ItemStack*)item)->setUnbreakable(value);
    });
    RemoteCall::exportAs("GMLIB_API", "getItemShouldKeepOnDeath", [](ItemStack const* item) -> bool {
        return ((gmlib::world::ItemStack*)item)->getShouldKeepOnDeath();
    });
    RemoteCall::exportAs("GMLIB_API", "setItemShouldKeepOnDeath", [](ItemStack const* item, bool value) -> void {
        ((gmlib::world::ItemStack*)item)->setShouldKeepOnDeath(value);
    });
    RemoteCall::exportAs("GMLIB_API", "getItemLockMode", [](ItemStack const* item) -> int {
        return (int)((gmlib::world::ItemStack*)item)->getItemLockMode();
    });
    RemoteCall::exportAs("GMLIB_API", "setItemLockMode", [](ItemStack const* item, int value) -> void {
        ((gmlib::world::ItemStack*)item)->setItemLockMode((ItemLockMode)value);
    });
    RemoteCall::exportAs("GMLIB_API", "getItemRepairCost", [](ItemStack const* item) -> int {
        return item->getBaseRepairCost();
    });
    RemoteCall::exportAs("GMLIB_API", "setItemRepairCost", [](ItemStack* item, int cost) -> void {
        (*item).setRepairCost(cost);
    });
    RemoteCall::exportAs("GMLIB_API", "getItemCanDestroy", [](ItemStack const* item) -> std::vector<std::string> {
        std::vector<std::string> result = {};
        for (auto& block : ((gmlib::world::ItemStack*)item)->getCanDestroy()) {
            result.push_back(block->getTypeName());
        }
        return result;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setItemCanDestroy",
        [](ItemStack const* item, std::vector<std::string> blocks) -> void {
            ((gmlib::world::ItemStack*)item)->setCanDestroy(blocks);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getItemCanPlaceOn", [](ItemStack const* item) -> std::vector<std::string> {
        std::vector<std::string> result = {};
        for (auto& block : ((gmlib::world::ItemStack*)item)->getCanPlaceOn()) {
            result.push_back(block->getTypeName());
        }
        return result;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setItemCanPlaceOn",
        [](ItemStack const* item, std::vector<std::string> blocks) -> void {
            ((gmlib::world::ItemStack*)item)->setCanPlaceOn(blocks);
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
        [](Player* player, int containerId, int slot, ItemStack const* item) -> void {
            InventorySlotPacket((ContainerID)containerId, slot, *item).sendTo(*player);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getContainerType", [](Container* container) -> std::string {
        return magic_enum::enum_name(container->getContainerType()).data();
    });
    RemoteCall::exportAs("GMLIB_API", "hasPlayerNbt", [](std::string const& uuid) -> bool {
        return gmlib::world::Player::getPlayerNbt(mce::UUID::fromString(uuid)) != nullptr;
    });
    RemoteCall::exportAs("GMLIB_API", "getItemMaxCount", [](ItemStack const* item) -> int {
        return item->getMaxStackSize();
    });
    RemoteCall::exportAs("GMLIB_API", "entityHasFamily", [](Actor* entity, std::string const& family) -> bool {
        return entity->hasFamily(HashedString(family));
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerDestroyBlockProgress", [](Player* player, Block const* block) -> float {
        return player->getDestroyProgress(*block);
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityEffectVisible", [](Actor* entity, int effectId) -> bool {
        if (auto effect = entity->getEffect(effectId)) {
            return effect->mEffectVisible;
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityEffectDuration", [](Actor* entity, int effectId) -> int {
        if (auto effect = entity->getEffect(effectId)) {
            return effect->mDuration;
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityEffectDurationEasy", [](Actor* entity, int effectId) -> int {
        if (auto effect = entity->getEffect(effectId)) {
            return effect->mDurationEasy;
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityEffectDurationHard", [](Actor* entity, int effectId) -> int {
        if (auto effect = entity->getEffect(effectId)) {
            return effect->mDurationHard;
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityEffectDurationNormal", [](Actor* entity, int effectId) -> int {
        if (auto effect = entity->getEffect(effectId)) {
            return effect->mDurationNormal;
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityEffectAmplifier", [](Actor* entity, int effectId) -> int {
        if (auto effect = entity->getEffect(effectId)) {
            return effect->mAmplifier;
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityEffectAmbient", [](Actor* entity, int effectId) -> bool {
        if (auto effect = entity->getEffect(effectId)) {
            return effect->mAmbient;
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "entityHasEffect", [](Actor* entity, int effectId) -> int {
        return entity->hasEffect(*MobEffect::getById(effectId));
    });
    RemoteCall::exportAs("GMLIB_API", "getGameDifficulty", []() -> int {
        return ll::service::getLevel().transform(
                                          [](Level& level) -> int { return (int)level.getDifficulty(); }
        ).value_or(-1);
    });
    RemoteCall::exportAs("GMLIB_API", "setGameDifficulty", [](int difficulty) -> void {
        if (auto level = ll::service::getLevel()) {
            level->setDifficulty((Difficulty)difficulty);
        }
    });
    RemoteCall::exportAs("GMLIB_API", "getDefaultGameMode", []() -> int {
        return ll::service::getLevel().transform([](Level& level) -> int { return (int)level.getDefaultGameType(); }).value_or(-1);
    });
    RemoteCall::exportAs("GMLIB_API", "setDefaultGameMode", [](int gameMode) -> void {
        if (auto level = ll::service::getLevel()) {
            level->setDefaultGameType((GameType)gameMode);
        }
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "registerCustomShapelessRecipe",
        [](std::string const& recipe_id, std::vector<std::string> ingredients, ItemStack* result) -> void {
            if (!gmlib::world::Level::getInstance().has_value()) return;
            std::vector<Recipes::Type> types;
            char                       rt = 'A';
            for (auto& ing : ingredients) {
                types.emplace_back(ing, rt++, 1, 0);
            }
            gmlib::mod::recipe::RecipeRegistry::registerShapelessCraftingTableRecipe(recipe_id, types, *result);
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "registerCustomShapedRecipe",
        [](std::string const&       recipe_id,
           std::vector<std::string> shape,
           std::vector<std::string> ingredients,
           ItemStack*               result) -> void {
            if (!gmlib::world::Level::getInstance().has_value()) return;
            std::vector<Recipes::Type> types;
            char                       rt = 'A';
            for (auto& ing : ingredients) {
                types.emplace_back(ing, rt++, 1, 0);
            }
            gmlib::mod::recipe::RecipeRegistry::registerShapedCraftingTableRecipe(recipe_id, shape, types, *result);
        }
    );
}