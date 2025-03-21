#include "Global.h"
#include <regex>

ActorUniqueID parseScriptUniqueID(std::string const& uniqueId) {
    return StringUtils::isInteger(uniqueId) ? ActorUniqueID(std::stoll(uniqueId)) : ActorUniqueID::INVALID_ID();
}

void Export_Compatibility_API() {
    RemoteCall::exportAs("GMLIB_API", "unregisterRecipe", [](std::string const& id) -> bool {
        // return GMLevel::getInstance().has_value() ? GMLIB::Mod::CustomRecipe::unregisterRecipe(id) : false;
        throw std::runtime_error("GMLIB_API::unregisterRecipe is not implemented");
    });
    RemoteCall::exportAs("GMLIB_API", "setCustomPackPath", [](std::string const& path) -> void {
        AddonsLoaderUtils::addCustomPackPath(path);
    });
    RemoteCall::exportAs("GMLIB_API", "getServerMspt", []() -> double {
        return GMLevel::getInstance().transform(
                                             [](GMLevel& level) -> double { return level.getServerMspt(); }
        ).value_or(0.0);
    });
    RemoteCall::exportAs("GMLIB_API", "getServerCurrentTps", []() -> float {
        return GMLevel::getInstance()
            .transform([](GMLevel& level) -> float { return level.getServerCurrentTps(); })
            .value_or(0.0);
    });
    RemoteCall::exportAs("GMLIB_API", "getServerAverageTps", []() -> double {
        return GMLevel::getInstance()
            .transform([](GMLevel& level) -> double { return level.getServerAverageTps(); })
            .value_or(0.0);
    });
    RemoteCall::exportAs("GMLIB_API", "getAllPlayerUuids", []() -> std::vector<std::string> {
        std::vector<std::string> result;
        for (auto& player : OfflinePlayer::getAllOfflinePlayers()) {
            result.push_back(player.getUUID().asString());
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerNbt", [](std::string const& uuid) -> std::unique_ptr<CompoundTag> {
        if (auto player = OfflinePlayer::getOfflinePlayer(mce::UUID::fromString(uuid))) {
            return std::make_unique<CompoundTag>(*player->getNbt());
        }
        return nullptr;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerNbt",
        [](std::string const& uuid, CompoundTag* nbt, bool forceCreate) -> bool {
            if (auto player = OfflinePlayer::getOfflinePlayer(mce::UUID::fromString(uuid))) return player->setNbt(*nbt);
            return forceCreate ? OfflinePlayer::createNewPlayerNbt(mce::UUID::fromString(uuid), *nbt).has_value()
                               : false;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerNbtTags",
        [](std::string const& uuid, CompoundTag* nbt, std::vector<std::string> tags) -> bool {
            if (auto player = OfflinePlayer::getOfflinePlayer(mce::UUID::fromString(uuid))) {
                auto nbt2 = *player->getNbt();
                GMCompoundTag::writeNbtTags(nbt2, *nbt, tags);
                return player->setNbt(nbt2);
            }
            return false;       
        }
    );
    RemoteCall::exportAs("GMLIB_API", "deletePlayerNbt", [](std::string const& uuid) -> bool {
        return OfflinePlayer::deletePlayerNbt(mce::UUID::fromString(uuid));
    });
    RemoteCall::exportAs("GMLIB_API", "getAllExperiments", []() -> std::vector<int> {
        // std::vector<int> result;
        // for (auto& key : GMLevel::getAllExperiments()) {
        //     result.push_back((int)key);
        // }
        // return result;
        throw std::runtime_error("GMLIB_API::getAllExperiments is not implemented");
    });
    RemoteCall::exportAs("GMLIB_API", "getExperimentTranslateKey", [](int id) -> std::string {
        // std::string result;
        // try {
        //     result = Experiments::getExperimentTextID(AllExperiments(id));
        // } catch (...) {}
        // return result;
        throw std::runtime_error("GMLIB_API::getExperimentTranslateKey is not implemented");
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "createFloatingText",
        [](std::pair<Vec3, int> pos, std::string const& text, bool papi) -> uint64 {
            return FloatingTextManager::getInstance()
                .addStatic(text, pos.first, pos.second, papi)
                .lock()
                ->getRuntimeID();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "setFloatingTextData", [](uint64 id, std::string const& text) -> bool {
        if (auto ft = FloatingTextManager::getInstance().get(id); !ft.expired()) {
            ft.lock()->setText(text);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "deleteFloatingText", [](uint64 id) -> bool {
        return FloatingTextManager::getInstance().remove(id);
    });
    RemoteCall::exportAs("GMLIB_API", "sendFloatingTextToPlayer", [](uint64 id, Player* pl) -> bool {
        if (auto ft = FloatingTextManager::getInstance().get(id); !ft.expired()) {
            ft.lock()->sendTo((GMPlayer&)*pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "sendFloatingText", [](uint64 id) -> bool {
        if (auto ft = FloatingTextManager::getInstance().get(id); !ft.expired()) {
            ft.lock()->sendToClients();
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "removeFloatingTextFromPlayer", [](uint64 id, Player* pl) -> bool {
        if (auto ft = FloatingTextManager::getInstance().get(id); !ft.expired()){
            ft.lock()->removeFrom((GMPlayer&)*pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "removeFloatingText", [](uint64 id) -> bool {
        if (auto ft = FloatingTextManager::getInstance().get(id); !ft.expired()) {
            ft.lock()->removeFromClients();
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "updateClientFloatingTextData", [](uint64 id, Player* pl) -> bool {
        if (auto ft = FloatingTextManager::getInstance().get(id); !ft.expired()) {
            ft.lock()->update((GMPlayer&)*pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "updateAllClientsFloatingTextData", [](uint64 id) -> bool {
        if (auto ft = FloatingTextManager::getInstance().get(id); !ft.expired()) {
            ft.lock()->updateClients();
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "isVersionMatched", [](std::uint16_t a, std::uint16_t b, std::uint16_t c) -> bool {
        return LIB_VERSION >= ll::data::Version(a, b, c, "", "");
    });
    RemoteCall::exportAs("GMLIB_API", "getVersion_LRCA", []() -> std::string { return LIB_VERSION.to_string(); });
    RemoteCall::exportAs("GMLIB_API", "getVersion_GMLIB", []() -> std::string {
        return GMLIB_VERSION_TO_STRING(GMLIB_VERSION_MAJOR) "." GMLIB_VERSION_TO_STRING(GMLIB_VERSION_MINOR
        ) "." GMLIB_VERSION_TO_STRING(GMLIB_VERSION_PATCH);
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
        if (GMLevel::getInstance()) {
            I18nAPI::chooseLanguage(code);
        }
    });
    RemoteCall::exportAs("GMLIB_API", "getResourcePackI18nLanguage", []() -> std::string {
        return GMLevel::getInstance().has_value() ? I18nAPI::getCurrentLanguageCode() : "unknown";
    });
    RemoteCall::exportAs("GMLIB_API", "getSupportedLanguages", []() -> std::vector<std::string> {
        return GMLevel::getInstance() ? I18nAPI::getSupportedLanguageCodes() : std::vector<std::string>();
    });
    RemoteCall::exportAs("GMLIB_API", "loadLanguage", [](std::string const& code, std::string const& lang) -> void {
        if (GMLevel::getInstance()) {
            I18nAPI::loadLanguage(code, lang);
        }
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "updateOrCreateLanguageFile",
        [](std::string const& code, std::unordered_map<std::string, std::string> lang, std::string const& path
        ) -> void {
            if (GMLevel::getInstance()) {
                I18nAPI::updateOrCreateLanguageFile(path, code, lang);
            }
        }
    );
    RemoteCall::exportAs("GMLIB_API", "loadLanguagePath", [](std::string const& path) -> void {
        if (GMLevel::getInstance()) {
            I18nAPI::loadLanguagesFromDirectory(path);
        }
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerPosition", [](std::string const& uuid) -> std::pair<BlockPos, int> {
        if (auto player = OfflinePlayer::getOfflinePlayer(mce::UUID::fromString(uuid))) {
            if (auto pos = player->getPlayerPosition()) {
                return *pos;
            }
        }
        return {
            {0, 0, 0},
            0
        };
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerPosition",
        [](std::string const& uuid, std::pair<BlockPos, int> pos) -> bool {
            // return GMPlayer::setPlayerPosition(mce::UUID::fromString(uuid), pos.first, pos.second);
            throw std::runtime_error("GMLIB_API::setPlayerPosition is not implemented");
        }
    );
    RemoteCall::exportAs("GMLIB_API", "playerHasScore", [](std::string const& uuid, std::string const& obj) -> bool {
        return GMScoreboard::getInstance()->getPlayerScore(obj, mce::UUID::fromString(uuid)).has_value();
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerScore", [](std::string const& uuid, std::string const& obj) -> int {
        return GMScoreboard::getInstance()->getPlayerScore(obj, mce::UUID::fromString(uuid)).value_or(0);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "addPlayerScore",
        [](std::string const& uuid, std::string const& obj, int value) -> bool {
            return GMScoreboard::getInstance()
                ->setPlayerScore(obj, mce::UUID::fromString(uuid), value, PlayerScoreSetFunction::Add)
                .has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "reducePlayerScore",
        [](std::string const& uuid, std::string const& obj, int value) -> bool {
            return GMScoreboard::getInstance()
                ->setPlayerScore(obj, mce::UUID::fromString(uuid), value, PlayerScoreSetFunction::Subtract)
                .has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "setPlayerScore",
        [](std::string const& uuid, std::string const& obj, int value) -> bool {
            return GMScoreboard::getInstance()->setPlayerScore(obj, mce::UUID::fromString(uuid), value).has_value();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "resetPlayerScore", [](std::string const& uuid, std::string const& obj) -> bool {
        return GMScoreboard::getInstance()->resetPlayerScore(obj, mce::UUID::fromString(uuid));
    });
    RemoteCall::exportAs("GMLIB_API", "resetPlayerScores", [](std::string const& uuid) -> bool {
        return GMScoreboard::getInstance()->resetPlayerScore(mce::UUID::fromString(uuid));
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "entityHasScore",
        [](std::string const& uniqueId, std::string const& obj) -> bool {
            return GMScoreboard::getInstance()->getScore(obj, parseScriptUniqueID(uniqueId)).has_value();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getEntityScore", [](std::string const& uniqueId, std::string const& obj) -> int {
        return GMScoreboard::getInstance()->getScore(obj, parseScriptUniqueID(uniqueId)).value_or(0);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "addEntityScore",
        [](std::string const& uniqueId, std::string const& obj, int value) -> bool {
            return GMScoreboard::getInstance()
                ->setScore(obj, parseScriptUniqueID(uniqueId), value, PlayerScoreSetFunction::Add)
                .has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "reduceEntityScore",
        [](std::string const& uniqueId, std::string const& obj, int value) -> bool {
            return GMScoreboard::getInstance()
                ->setScore(obj, parseScriptUniqueID(uniqueId), value, PlayerScoreSetFunction::Subtract)
                .has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "setEntityScore",
        [](std::string const& uniqueId, std::string const& obj, int value) -> bool {
            return GMScoreboard::getInstance()->setScore(obj, parseScriptUniqueID(uniqueId), value).has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "resetEntityScore",
        [](std::string const& uniqueId, std::string const& obj) -> bool {
            return GMScoreboard::getInstance()->resetScore(obj, parseScriptUniqueID(uniqueId));
        }
    );
    RemoteCall::exportAs("GMLIB_API", "resetEntityScores", [](std::string const& uniqueId) -> bool {
        return GMScoreboard::getInstance()->resetScore(parseScriptUniqueID(uniqueId));
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "fakePlayerHasScore",
        [](std::string const& name, std::string const& obj) -> bool {
            return GMScoreboard::getInstance()->getScore(obj, name).has_value();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getFakePlayerScore", [](std::string const& name, std::string const& obj) -> int {
        return GMScoreboard::getInstance()->getScore(obj, name).value_or(0);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "addFakePlayerScore",
        [](std::string const& name, std::string const& obj, int value) -> bool {
            return GMScoreboard::getInstance()->setScore(obj, name, value, PlayerScoreSetFunction::Add).has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "reduceFakePlayerScore",
        [](std::string const& name, std::string const& obj, int value) -> bool {
            return GMScoreboard::getInstance()
                ->setScore(obj, name, value, PlayerScoreSetFunction::Subtract)
                .has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "setFakePlayerScore",
        [](std::string const& name, std::string const& obj, int value) -> bool {
            return GMScoreboard::getInstance()->setScore(obj, name, value).has_value();
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "resetFakePlayerScore",
        [](std::string const& name, std::string const& obj) -> bool {
            return GMScoreboard::getInstance()->resetScore(obj, name);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "resetFakePlayerScores", [](std::string const& name) -> bool {
        return GMScoreboard::getInstance()->resetScore(name);
    });
    RemoteCall::exportAs("GMLIB_API", "addObjective", [](std::string const& obj) -> bool {
        return GMScoreboard::getInstance()->addObjective(obj).has_value();
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "addObjectiveWithDisplayName",
        [](std::string const& obj, std::string const& displayName) -> bool {
            return GMScoreboard::getInstance()->addObjective(obj, displayName).has_value();
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getDisplayName", [](std::string const& obj) -> std::string {
        return GMScoreboard::getInstance()->getObjectiveDisplayName(obj).value_or("");
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setDisplayName",
        [](std::string const& obj, std::string const& displayName) -> bool {
            return GMScoreboard::getInstance()->setObjectiveDisplayName(obj, displayName);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "removeObjective", [](std::string const& obj) -> bool {
        return GMScoreboard::getInstance()->removeObjective(obj);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setDisplayObjective",
        [](std::string const& obj, std::string const& slot, int order) -> void {
            return GMScoreboard::getInstance()->setObjectiveDisplay(obj, slot, (ObjectiveSortOrder)order);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "clearDisplayObjective", [](std::string const& slot) -> void {
        return GMScoreboard::getInstance()->clearObjectiveDisplay(slot);
    });
    RemoteCall::exportAs("GMLIB_API", "getAllObjectives", []() -> std::vector<std::string> {
        std::vector<std::string> result;
        for (auto& obj : GMScoreboard::getInstance()->getObjectives()) {
            result.push_back(obj->mName);
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getAllScoreboardPlayers", []() -> std::vector<std::string> {
        std::vector<std::string> result;
        for (auto& player : GMScoreboard::getInstance()->getAllPlayers()) {
            result.push_back(player.getUUID().asString());
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getAllScoreboardFakePlayers", []() -> std::vector<std::string> {
        std::vector<std::string> result;
        for (auto& name : GMScoreboard::getInstance()->getAllFakePlayers()) {
            result.push_back(name);
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getAllScoreboardEntities", []() -> std::vector<std::string> {
        std::vector<std::string> result;
        for (auto& uniqueId : GMScoreboard::getInstance()->getAllEntities()) {
            result.push_back(std::to_string(uniqueId.rawID));
        }
        return result;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "getAllTrackedTargets",
        []() -> std::vector<std::unordered_map<std::string, std::string>> {
            std::vector<std::unordered_map<std::string, std::string>> result;
            for (auto& player : GMScoreboard::getInstance()->getAllPlayers()) {
                result.push_back({
                    {"Type", "Player"       },
                    {"Uuid", player.getUUID().asString()}
                });
            }
            for (auto& name : GMScoreboard::getInstance()->getAllFakePlayers()) {
                result.push_back({
                    {"Type", "FakePlayer"},
                    {"Name", name        }
                });
            }
            for (auto& uniqueId : GMScoreboard::getInstance()->getAllEntities()) {
                result.push_back({
                    {"Type",     "Entity"                   },
                    {"UniqueId", std::to_string(uniqueId.rawID)}
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
        return ll::service::getLevel()->fetchEntity(parseScriptUniqueID(uniqueId), false);
    });
    RemoteCall::exportAs("GMLIB_API", "getWorldSpawn", []() -> std::pair<BlockPos, int> {
        return {GMLevel::getInstance()->getLevelData().getSpawnPos(), 0};
    });
    RemoteCall::exportAs("GMLIB_API", "setWorldSpawn", [](std::pair<BlockPos, int> pos) -> bool {
        if (pos.second != 0) return false;
        GMLevel::getInstance()->getLevelData().setSpawnPos(pos.first);
        auto pkt = SetSpawnPositionPacket();
        pkt.mSpawnBlockPos = NetworkBlockPosition(pos.first);
        pkt.mDimensionType = 0;
        pkt.mSpawnPosType = SpawnPositionType::WorldSpawn;
        pkt.sendToClients();
        return true;
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerSpawnPoint", [](Player* pl) -> std::pair<BlockPos, int> {
        // auto res = ((GMPlayer*)pl)->getSpawnPoint();
        // return {res.first, res.second};
        throw std::runtime_error("GMLIB_API::getPlayerSpawnPoint is not implemented");
    });
    RemoteCall::exportAs("GMLIB_API", "setPlayerSpawnPoint", [](Player* pl, std::pair<BlockPos, int> pos) -> void {
        // ((GMPlayer*)pl)->setSpawnPoint(pos.first, pos.second);
        throw std::runtime_error("GMLIB_API::setPlayerSpawnPoint is not implemented");
    });
    RemoteCall::exportAs("GMLIB_API", "clearPlayerSpawnPoint", [](Player* pl) -> void {
        // ((GMPlayer*)pl)->clearSpawnPoint();
        throw std::runtime_error("GMLIB_API::clearPlayerSpawnPoint is not implemented");
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
        return UserCache::getXuidByUuid(mce::UUID::fromString(uuid)).value_or("");
    });
    RemoteCall::exportAs("GMLIB_API", "getXuidByName", [](std::string const& name) -> std::string {
        return UserCache::getXuidByName(name).value_or("");
    });
    RemoteCall::exportAs("GMLIB_API", "getNameByUuid", [](std::string const& uuid) -> std::string {
        return UserCache::getNameByUuid(mce::UUID::fromString(uuid)).value_or("");
    });
    RemoteCall::exportAs("GMLIB_API", "getNameByXuid", [](std::string const& xuid) -> std::string {
        return UserCache::getNameByXuid(xuid).value_or("");
    });
    RemoteCall::exportAs("GMLIB_API", "getUuidByXuid", [](std::string const& xuid) -> std::string {
        return UserCache::getUuidByXuid(xuid)
            .transform([](mce::UUID&& uuid) -> std::string { return uuid.asString(); })
            .value_or("");
    });
    RemoteCall::exportAs("GMLIB_API", "getUuidByName", [](std::string const& name) -> std::string {
        return UserCache::getUuidByName(name)
            .transform([](mce::UUID&& uuid) -> std::string { return uuid.asString(); })
            .value_or("");
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "getAllPlayerInfo",
        []() -> std::vector<std::unordered_map<std::string, std::string>> {
            std::vector<std::unordered_map<std::string, std::string>> result;
            for (auto entry : UserCache::entries()){
                result.push_back({
                    {"Name", entry.mName           },
                    {"Xuid", entry.mXuid           },
                    {"Uuid", entry.mUuid.asString()}
                });
            }
            return result;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getBlockRuntimeId", [](std::string const& blockName, short legacyData) -> uint {
        return Block::tryGetFromRegistry(blockName, legacyData)
            .transform([](const Block& block) -> uint { return block.mNetworkId; })
            .value_or(0);
    });
    RemoteCall::exportAs("GMLIB_API", "getBlockTranslateKey", [](Block const* block) -> std::string {
        return block->getLegacyBlock().mDescriptionId;
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
            if (auto nbt = GMCompoundTag::readFromFile(path, isBinary)) {
                return std::make_unique<CompoundTag>(nbt.value());
            }
            return nullptr;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "saveNbtToFile",
        [](std::string const& path, CompoundTag* nbt, bool isBinary) -> bool {
            return GMCompoundTag::saveToFile(path, *nbt, isBinary);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getBlockDestroySpeed", [](Block const* block) -> float {
        return block->mDirectData->mUnkc08fbd.as<float>();
    });
    RemoteCall::exportAs("GMLIB_API", "getDestroyBlockSpeed", [](ItemStack const* item, Block const* block) -> float {
        // return item->getDestroySpeed(*block);
        throw std::runtime_error("GMLIB_API::getDestroyBlockSpeed is not implemented");
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "playerDestroyBlock",
        [](Block const* block, std::pair<BlockPos, int> pos, Player* player) -> void {
            return block->playerDestroy(*player, pos.first);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "itemCanDestroyBlock", [](ItemStack const* item, Block const* block) -> bool {
        return std::ranges::any_of(item->mCanDestroy, [block](BlockLegacy const* blockLegacy) {
            return block->getTypeName() == blockLegacy->getTypeName();
        });
    });
    RemoteCall::exportAs("GMLIB_API", "itemCanDestroyInCreative", [](ItemStack const* item) -> bool {
        if (auto itemDef = item->getItem()) {
            return itemDef->canDestroyInCreative();
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "itemCanDestroySpecial", [](ItemStack const* item, Block const* block) -> bool {
        // return item->canDestroySpecial(*block);
        throw std::runtime_error("GMLIB_API::itemCanDestroySpecial is not implemented");
    });
    RemoteCall::exportAs("GMLIB_API", "blockCanDropWithAnyTool", [](Block const* block) -> bool {
        return !block->getLegacyBlock().mRequiresCorrectToolForDrops;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "blockPlayerWillDestroy",
        [](Block const* block, Player* player, std::pair<BlockPos, int> pos) -> bool {
            return block->getLegacyBlock().playerWillDestroy(*player, pos.first, *block);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "playerAttack", [](Player* player, Actor* entity) -> bool {
        return player->attack(*entity, SharedTypes::Legacy::ActorDamageCause::EntityAttack);
    });
    RemoteCall::exportAs("GMLIB_API", "playerPullInEntity", [](Player* player, Actor* entity) -> bool {
        // return player->pullInEntity(*entity);
        throw std::runtime_error("GMLIB_API::playerPullInEntity is not implemented");
    });
    RemoteCall::exportAs("GMLIB_API", "getBlockTranslateKeyFromName", [](std::string const& blockName) -> std::string {
        return Block::tryGetFromRegistry(blockName)
            .transform([](const Block& block) -> std::string { return block.buildDescriptionName(); })
            .value_or("tile.unknown.name");
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "getBlockLightEmission",
        [](std::string const& blockName, short legacyData) -> char {
            return Block::tryGetFromRegistry(blockName)
                .transform([](const Block& block) -> char { return block.mDirectData->mUnkda4e0e.as<char>(); })
                .value_or(-1);
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "getGameRules",
        []() -> std::vector<std::unordered_map<std::string, std::string>> {
            std::vector<std::unordered_map<std::string, std::string>> result;
            for (auto& gameRule : ll::service::getLevel()->getGameRules().mGameRules.get()) {
                switch (gameRule.mType) {
                case GameRule::Type::Bool:
                    result.push_back({
                        {"Name",  gameRule.mName                },
                        {"Type",  "Bool"                            },
                        {"Value", std::to_string(gameRule.mValue->mUnk29fff1.as<bool>())}
                    });
                    break;
                case GameRule::Type::Float:
                    result.push_back({
                        {"Name",  gameRule.mName                 },
                        {"Type",  "Float"                            },
                        {"Value", std::to_string(gameRule.mValue->mUnk768db5.as<float>())}
                    });
                    break;
                case GameRule::Type::Int:
                    result.push_back({
                        {"Name",  gameRule.mName               },
                        {"Type",  "Int"                            },
                        {"Value", std::to_string(gameRule.mValue->mUnk2ab4f3.as<int>())}
                    });
                    break;
                case GameRule::Type::Invalid:
                    break;
                }
            }
            return result;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getEnchantTypeNameFromId", [](size_t id) -> std::string {
        if (id < Enchant::mEnchants().size()){
            return Enchant::mEnchants()[id]->mStringId->getString();
        }
        return "";
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "applyEnchant",
        [](ItemStack* item, std::string const& typeName, int level, bool allowNonVanilla) -> bool {
            return EnchantUtils::applyEnchant(
                *item,
                Enchant::mEnchantNameToType()[HashedString(typeName)],
                level,
                allowNonVanilla
            );
        }
    );
    RemoteCall::exportAs("GMLIB_API", "removeEnchants", [](ItemStack* item) -> void {
        item->removeEnchants();
    });
    RemoteCall::exportAs("GMLIB_API", "hasEnchant", [](ItemStack* item, std::string const& typeName) -> bool {
        return EnchantUtils::hasEnchant(Enchant::mEnchantNameToType()[HashedString(typeName)], *item);
    });
    RemoteCall::exportAs("GMLIB_API", "getEnchantLevel", [](ItemStack* item, std::string const& typeName) -> int {
        return EnchantUtils::getEnchantLevel(Enchant::mEnchantNameToType()[HashedString(typeName)], *item);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "getEnchantNameAndLevel",
        [](std::string const& typeName, int level) -> std::string {
            return EnchantUtils::getEnchantNameAndLevel(Enchant::mEnchantNameToType()[HashedString(typeName)], level);
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "dropPlayerItem",
        [](Player* player, ItemStack const* item, bool randomly) -> bool { return player->drop(*item, randomly); }
    );
    RemoteCall::exportAs("GMLIB_API", "getPlayerRuntimeId", [](Player* player) -> uint64 {
        return player->getRuntimeID().rawID;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityRuntimeId", [](Actor* entity) -> uint64 {
        return entity->getRuntimeID().rawID;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityNameTag", [](Actor* entity) -> std::string {
        return entity->getNameTag();
    });
    RemoteCall::exportAs("GMLIB_API", "ItemisUnbreakable", [](ItemStack const* item) -> bool {
        return ((GMItemStack*)item)->isUnbreakable();
    });
    RemoteCall::exportAs("GMLIB_API", "setItemUnbreakable", [](ItemStack const* item, bool value) -> void {
        ((GMItemStack*)item)->setUnbreakable(value);
    });
    RemoteCall::exportAs("GMLIB_API", "getItemShouldKeepOnDeath", [](ItemStack const* item) -> bool {
        return ((GMItemStack*)item)->getShouldKeepOnDeath();
    });
    RemoteCall::exportAs("GMLIB_API", "setItemShouldKeepOnDeath", [](ItemStack const* item, bool value) -> void {
        auto nbt = ((GMItemStack*)item)->getNbt();
        if (value) {
            (*nbt)["tags"]["minecraft:keep_on_death"] = true;
        }else{
            if (nbt->contains("tags") && (*nbt)["tags"].contains("minecraft:keep_on_death")){
                (*nbt)["tags"].get<CompoundTag>().erase("minecraft:keep_on_death");
            }
        }
        ((GMItemStack*)item)->setNbt(*nbt);
    });
    RemoteCall::exportAs("GMLIB_API", "getItemLockMode", [](ItemStack const* item) -> int {
        return (int)((GMItemStack*)item)->getItemLockMode();
    });
    RemoteCall::exportAs("GMLIB_API", "setItemLockMode", [](ItemStack const* item, int value) -> void {
        ((GMItemStack*)item)->setItemLockMode((ItemLockMode)value);
    });
    RemoteCall::exportAs("GMLIB_API", "getItemRepairCost", [](ItemStack const* item) -> int {
        return item->getBaseRepairCost();
    });
    RemoteCall::exportAs("GMLIB_API", "setItemRepairCost", [](ItemStack* item, int cost) -> void {
        (*item).setRepairCost(cost);
    });
    RemoteCall::exportAs("GMLIB_API", "getItemCanDestroy", [](ItemStack const* item) -> std::vector<std::string> {
        std::vector<std::string> result = {};
        for (auto& block : ((GMItemStack*)item)->mCanDestroy) {
            result.push_back(block->getTypeName());
        }
        return result;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setItemCanDestroy",
        [](ItemStack const* item, std::vector<std::string> blocks) -> void {
            std::vector<const BlockLegacy*> data;
            for (auto& name : blocks) {
                if (auto block = BlockLegacy::tryGetFromRegistry(name)) {
                    data.push_back(block.as_ptr());
                }
            }
            ((GMItemStack*)item)->mCanDestroy = data;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getItemCanPlaceOn", [](ItemStack const* item) -> std::vector<std::string> {
        std::vector<std::string> result = {};
        for (auto& block : ((GMItemStack*)item)->mCanPlaceOn) {
            result.push_back(block->getTypeName());
        }
        return result;
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "setItemCanPlaceOn",
        [](ItemStack const* item, std::vector<std::string> blocks) -> void {
            std::vector<const BlockLegacy*> data;
            for (auto& name : blocks) {
                if (auto block = BlockLegacy::tryGetFromRegistry(name)) {
                    data.push_back(block.as_ptr());
                }
            }
            ((GMItemStack*)item)->mCanPlaceOn = data;
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getPlayerHungry", [](Player* player) -> float {
        return player->getMutableAttribute(Player::HUNGER()).mInstance->mCurrentValue;
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerArmorCoverPercentage", [](Player* player) -> float {
        return player->getArmorCoverPercentage();
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerArmorValue", [](Player* player) -> int {
        return player->getArmorValue();
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityOwnerUniqueId", [](Actor* entity) -> int64 {
        return entity->getOwnerId().rawID;
    });
    RemoteCall::exportAs("GMLIB_API", "getItemCategoryName", [](ItemStack const* item) -> std::string {
        if (auto item2 = item->mItem){
            return item2->buildCategoryDescriptionName();
        }
        return "";
    });
    RemoteCall::exportAs("GMLIB_API", "getItemCustomName", [](ItemStack const* item) -> std::string {
        return item->getCustomName();
    });
    RemoteCall::exportAs("GMLIB_API", "getItemEffecName", [](ItemStack const* item) -> std::string {
        if (auto item2 = item->mItem){
            return item2->buildEffectDescriptionName(*item);
        }
        return "";
    });
    RemoteCall::exportAs("GMLIB_API", "itemIsFood", [](ItemStack const* item) -> bool {
        if (auto itemDef = item->getItem()) {
            return itemDef->isFood();
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "setPlayerUIItem", [](Player* player, int slot, ItemStack const* item) -> void {
        player->setPlayerUIItem((PlayerUISlot)slot, *item, false);
    });
    RemoteCall::exportAs("GMLIB_API", "getPlayerUIItem", [](Player* player, int slot) -> ItemStack const* {
        return &player->mPlayerUIContainer->getItem(slot);
    });
    RemoteCall::exportAs(
        "GMLIB_API",
        "sendInventorySlotPacket",
        [](Player* player, int containerId, int slot, ItemStack const* item) -> void {
            InventorySlotPacket((ContainerID)containerId, slot, *item).sendTo(*player);
        }
    );
    RemoteCall::exportAs("GMLIB_API", "getContainerType", [](Container* container) -> std::string {
        return magic_enum::enum_name(container->mContainerType).data();
    });
    RemoteCall::exportAs("GMLIB_API", "hasPlayerNbt", [](std::string const& uuid) -> bool {
        return OfflinePlayer::getOfflinePlayer(mce::UUID::fromString(uuid)).transform([&](auto&& player) -> bool { return player.hasNbt(); }).value_or(false);
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
        if (effectId < 0 || !MobEffect::mMobEffects()[effectId]) return false;
        if (auto effect = entity->getEffect(*MobEffect::mMobEffects()[effectId])) {
            return effect->mEffectVisible;
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityEffectDuration", [](Actor* entity, int effectId) -> int {
        if (effectId < 0 || !MobEffect::mMobEffects()[effectId]) return false;
        if (auto effect = entity->getEffect(*MobEffect::mMobEffects()[effectId])) {
            return effect->mDuration->mValue;
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityEffectDurationEasy", [](Actor* entity, int effectId) -> int {
        if (effectId < 0 || !MobEffect::mMobEffects()[effectId]) return false;
        if (auto effect = entity->getEffect(*MobEffect::mMobEffects()[effectId])) {
            return effect->mDurationEasy->transform([](auto&& duration) -> int { return duration.mValue; }).value_or(0);
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityEffectDurationHard", [](Actor* entity, int effectId) -> int {
        if (effectId < 0 || !MobEffect::mMobEffects()[effectId]) return false;
        if (auto effect = entity->getEffect(*MobEffect::mMobEffects()[effectId])) {
            return effect->mDurationHard->transform([](auto&& duration) -> int { return duration.mValue; }).value_or(0);
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityEffectDurationNormal", [](Actor* entity, int effectId) -> int {
        if (effectId < 0 || !MobEffect::mMobEffects()[effectId]) return false;
        if (auto effect = entity->getEffect(*MobEffect::mMobEffects()[effectId])) {
            return effect->mDurationNormal->transform(
                                              [](auto&& duration) -> int { return duration.mValue; }
            ).value_or(0);
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityEffectAmplifier", [](Actor* entity, int effectId) -> int {
        if (effectId < 0 || !MobEffect::mMobEffects()[effectId]) return false;
        if (auto effect = entity->getEffect(*MobEffect::mMobEffects()[effectId])) {
            return effect->mAmplifier;
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityEffectAmbient", [](Actor* entity, int effectId) -> bool {
        if (effectId < 0 || !MobEffect::mMobEffects()[effectId]) return false;
        if (auto effect = entity->getEffect(*MobEffect::mMobEffects()[effectId])) {
            return effect->mAmbient;
        }
        return 0;
    });
    RemoteCall::exportAs("GMLIB_API", "entityHasEffect", [](Actor* entity, int effectId) -> bool {
        return effectId > 0x24 ? false : entity->hasEffect(*MobEffect::mMobEffects()[effectId]);
    });
    RemoteCall::exportAs("GMLIB_API", "getGameDifficulty", []() -> int {
        return ll::service::getLevel().transform(
                                          [](Level& level) -> int { return (int)level.getDifficulty(); }
        ).value_or(-1);
    });
    RemoteCall::exportAs("GMLIB_API", "setGameDifficulty", [](int difficulty) -> void {
        if (auto level = ll::service::getLevel()) {
            level->setDifficulty((SharedTypes::Legacy::Difficulty)difficulty);
        }
    });
    RemoteCall::exportAs("GMLIB_API", "getDefaultGameMode", []() -> int {
        return ll::service::getLevel().transform(
                                          [](Level& level) -> int { return (int)level.getDefaultGameType(); }
        ).value_or(-1);
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
            // if (!GMLevel::getInstance().has_value()) return;
            // std::vector<Recipes::Type> types;
            // char                       rt = 'A';
            // for (auto& ing : ingredients) {
            //     auto ingredient = RecipeIngredient{ing, 0,1};
            //     types.push_back(Recipes::Type{
            //         (Item*)ingredient.getItem(),
            //         ingredient.getBlock(),
            //         ingredient,
            //         rt++
            //     });
            // }
            // GMLIB::Mod::CustomRecipe::registerShapelessCraftingTableRecipe(recipe_id, types, *result);
            throw std::runtime_error("GMLIB_API::registerCustomShapelessRecipe is not implemented");
        }
    );
    RemoteCall::exportAs(
        "GMLIB_API",
        "registerCustomShapedRecipe",
        [](std::string const&       recipe_id,
           std::vector<std::string> shape,
           std::vector<std::string> ingredients,
           ItemStack*               result) -> void {
            if (!GMLevel::getInstance().has_value()) return;
            std::vector<Recipes::Type> types;
            char                       rt = 'A';
            for (auto& ing : ingredients) {
                auto ingredient = RecipeIngredient{ing, 0, 1};
                types.push_back(Recipes::Type{(Item*)ingredient.getItem(), ingredient.getBlock(), ingredient, rt++});
            }
            auto tmp     = RecipeUnlockingRequirement();
            tmp.mContext = RecipeUnlockingRequirement::UnlockingContext::AlwaysUnlocked;
            ll::service::bedrock::getLevel()->getRecipes().addShapedRecipe(
                recipe_id,
                ItemInstance(*result),
                shape,
                types,
                {"crafting_table"},
                50,
                nullptr,
                tmp,
                SemVersion(
                    1,
                    20,
                    80,
                    {"", Bedrock::StaticOptimizedString::StorageType::Static},
                    {"", Bedrock::StaticOptimizedString::StorageType::Static}
                ),
                true
            );
        }
    );
    RemoteCall::exportAs("GMLIB_API", "entityIsType", [](Actor* entity, int type) -> bool {
        return entity->isType((ActorType)type);
    });
    RemoteCall::exportAs("GMLIB_API", "entityHasType", [](Actor* entity, int type) -> bool {
        return entity->hasType((ActorType)type);
    });
    RemoteCall::exportAs("GMLIB_API", "getEntityTypeId", [](Actor* entity) -> int {
        return (int)entity->getEntityTypeId();
    });
}