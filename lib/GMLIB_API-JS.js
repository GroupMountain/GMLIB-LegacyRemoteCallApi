const GMLIB_API = {
    createFloatingText: ll.import("GMLIB_API", "createFloatingText"),
    deleteFloatingText: ll.import("GMLIB_API", "deleteFloatingText"),
    setFloatingTextData: ll.import("GMLIB_API", "setFloatingTextData"),
    sendFloatingTextToPlayer: ll.import("GMLIB_API", "sendFloatingTextToPlayer"),
    sendFloatingText: ll.import("GMLIB_API", "sendFloatingText"),
    removeFloatingTextFromPlayer: ll.import("GMLIB_API", "removeFloatingTextFromPlayer"),
    removeFloatingText: ll.import("GMLIB_API", "removeFloatingText"),
    updateClientFloatingTextData: ll.import("GMLIB_API", "updateClientFloatingTextData"),
    updateAllClientsFloatingTextData: ll.import("GMLIB_API", "updateAllClientsFloatingTextData"),
    getServerMspt: ll.import("GMLIB_API", "getServerMspt"),
    getServerCurrentTps: ll.import("GMLIB_API", "getServerCurrentTps"),
    getServerAverageTps: ll.import("GMLIB_API", "getServerAverageTps"),
    getAllPlayerUuids: ll.import("GMLIB_API", "getAllPlayerUuids"),
    getPlayerNbt: ll.import("GMLIB_API", "getPlayerNbt"),
    setPlayerNbt: ll.import("GMLIB_API", "setPlayerNbt"),
    setPlayerNbtTags: ll.import("GMLIB_API", "setPlayerNbtTags"),
    resourcePackTranslate: ll.import("GMLIB_API", "resourcePackTranslate"),
    chooseResourcePackI18nLanguage: ll.import("GMLIB_API", "chooseResourcePackI18nLanguage"),
    setEducationFeatureEnabled: ll.import("GMLib_ServerAPI", "setEducationFeatureEnabled"),
    registerAbilityCommand: ll.import("GMLib_ServerAPI", "registerAbilityCommand"),
    setEnableAchievement: ll.import("GMLib_ServerAPI", "setEnableAchievement"),
    setForceTrustSkins: ll.import("GMLib_ServerAPI", "setForceTrustSkins"),
    enableCoResourcePack: ll.import("GMLib_ServerAPI", "enableCoResourcePack"),
    getLevelName: ll.import("GMLib_ServerAPI", "getLevelName"),
    setLevelName: ll.import("GMLib_ServerAPI", "setLevelName"),
    setFakeSeed: ll.import("GMLib_ServerAPI", "setFakeSeed"),
    spawnEntity: ll.import("GMLib_ServerAPI", "spawnEntity"),
    shootProjectile: ll.import("GMLib_ServerAPI", "shootProjectile"),
    throwEntity: ll.import("GMLib_ServerAPI", "throwEntity"),
    PlayerToEntity: ll.import("GMLib_ServerAPI", "PlayerToEntity"),
    setUnknownBlockCleaner: ll.import("GMLib_ModAPI", "setUnknownBlockCleaner"),
    getAllExperiments: ll.import("GMLIB_API", "getAllExperiments"),
    getExperimentTranslatedName: ll.import("GMLIB_API", "getExperimentTranslatedName"),
    getExperimentEnabled: ll.import("GMLib_ModAPI", "getExperimentEnabled"),
    setExperimentEnabled: ll.import("GMLib_ModAPI", "setExperimentEnabled"),
    registerExperimentsRequire: ll.import("GMLib_ModAPI", "registerExperimentsRequire"),
    registerStoneCutterRecipe: ll.import("GMLib_ModAPI", "registerStoneCutterRecipe"),
    registerSmithingTrimRecipe: ll.import("GMLib_ModAPI", "registerSmithingTrimRecipe"),
    registerSmithingTransformRecipe: ll.import("GMLib_ModAPI", "registerSmithingTransformRecipe"),
    registerBrewingContainerRecipe: ll.import("GMLib_ModAPI", "registerBrewingContainerRecipe"),
    registerBrewingMixRecipe: ll.import("GMLib_ModAPI", "registerBrewingMixRecipe"),
    registerFurnaceRecipe: ll.import("GMLib_ModAPI", "registerFurnaceRecipe"),
    registerShapedRecipe: ll.import("GMLib_ModAPI", "registerShapedRecipe"),
    registerShapelessRecipe: ll.import("GMLib_ModAPI", "registerShapelessRecipe"),
    isVersionMatched: ll.import("GMLIB_API", "isVersionMatched"),
    getVersion_LRCA: ll.import("GMLIB_API", "getVersion_LRCA"),
    getVersion_GMLIB: ll.import("GMLIB_API", "getVersion_GMLIB"),
    getPlayerPosition: ll.import("GMLIB_API", "getPlayerPosition"),
    setPlayerPosition: ll.import("GMLIB_API", "setPlayerPosition"),
    playerHasScore: ll.import("GMLIB_API", "playerHasScore"),
    getPlayerScore: ll.import("GMLIB_API", "getPlayerScore"),
    addPlayerScore: ll.import("GMLIB_API", "addPlayerScore"),
    reducePlayerScore: ll.import("GMLIB_API", "reducePlayerScore"),
    setPlayerScore: ll.import("GMLIB_API", "setPlayerScore"),
    resetPlayerScore: ll.import("GMLIB_API", "resetPlayerScore"),
    resetPlayerScores: ll.import("GMLIB_API", "resetPlayerScores"),
    entityHasScore: ll.import("GMLIB_API", "entityHasScore"),
    getEntityScore: ll.import("GMLIB_API", "getEntityScore"),
    addEntityScore: ll.import("GMLIB_API", "addEntityScore"),
    reduceEntityScore: ll.import("GMLIB_API", "reduceEntityScore"),
    setEntityScore: ll.import("GMLIB_API", "setEntityScore"),
    resetEntityScore: ll.import("GMLIB_API", "resetEntityScore"),
    resetEntityScores: ll.import("GMLIB_API", "resetEntityScores"),
    fakePlayerHasScore: ll.import("GMLIB_API", "fakePlayerHasScore"),
    getFakePlayerScore: ll.import("GMLIB_API", "getFakePlayerScore"),
    addFakePlayerScore: ll.import("GMLIB_API", "addFakePlayerScore"),
    reduceFakePlayerScore: ll.import("GMLIB_API", "reduceFakePlayerScore"),
    setFakePlayerScore: ll.import("GMLIB_API", "setFakePlayerScore"),
    resetFakePlayerScore: ll.import("GMLIB_API", "resetFakePlayerScore"),
    resetFakePlayerScores: ll.import("GMLIB_API", "resetFakePlayerScores"),
    addObjective: ll.import("GMLIB_API", "addObjective"),
    addObjectiveWithDisplayName: ll.import("GMLIB_API", "addObjectiveWithDisplayName"),
    getDisplayName: ll.import("GMLIB_API", "getDisplayName"),
    setDisplayName: ll.import("GMLIB_API", "setDisplayName"),
    removeObjective: ll.import("GMLIB_API", "removeObjective"),
    setDisplayObjective: ll.import("GMLIB_API", "setDisplayObjective"),
    clearDisplayObjective: ll.import("GMLIB_API", "clearDisplayObjective"),
    getAllObjectives: ll.import("GMLIB_API", "getAllObjectives"),
    getAllScoreboardPlayers: ll.import("GMLIB_API", "getAllScoreboardPlayers"),
    getAllScoreboardFakePlayers: ll.import("GMLIB_API", "getAllScoreboardFakePlayers"),
    getAllScoreboardEntities: ll.import("GMLIB_API", "getAllScoreboardEntities"),
    getPlayerFromUuid: ll.import("GMLIB_API", "getPlayerFromUuid"),
    getPlayerFromUniqueId: ll.import("GMLIB_API", "getPlayerFromUniqueId"),
    getEntityFromUniqueId: ll.import("GMLIB_API", "getEntityFromUniqueId"),
    getWorldSpawn: ll.import("GMLIB_API", "getWorldSpawn"),
    setWorldSpawn: ll.import("GMLIB_API", "setWorldSpawn"),
    getPlayerSpawnPoint: ll.import("GMLIB_API", "getPlayerSpawnPoint"),
    setPlayerSpawnPoint: ll.import("GMLIB_API", "setPlayerSpawnPoint"),
    clearPlayerSpawnPoint: ll.import("GMLIB_API", "clearPlayerSpawnPoint")
}

const FloatingTextList = [];

class StaticFloatingText {
    constructor(pos, text, papi = true) {
        this.mPosition = pos;
        this.mText = text;
        this.mPlaceholderAPI = papi;
        this.mRuntimeId = GMLIB_API.createFloatingText(this.mPosition, this.mText, this.mPlaceholderAPI);
        FloatingTextList.push(this);
        this.sendToClients();
        mc.listen("onJoin", (pl) => {
            this.sendToClient(pl);
        });
    }

    sendToClient(player) {
        return GMLIB_API.sendFloatingTextToPlayer(this.mRuntimeId, player);
    }

    sendToClients() {
        return GMLIB_API.sendFloatingText(this.mRuntimeId);
    }

    removeFromClient(player) {
        return GMLIB_API.removeFloatingTextFromPlayer(this.mRuntimeId, player);
    }

    removeFromClients() {
        return GMLIB_API.removeFloatingText(this.mRuntimeId);
    }

    updateClient(player) {
        return GMLIB_API.updateClientFloatingTextData(this.mRuntimeId, player);
    }

    updateClients() {
        return GMLIB_API.updateAllClientsFloatingTextData(this.mRuntimeId);
    }

    getRuntimeId() {
        return this.mRuntimeId;
    }

    getText() {
        return this.mText;
    }

    setText(newText) {
        this.mText = newText;
    }

    update() {
        GMLIB_API.setFloatingTextData(this.mRuntimeId, this.mText);
        return this.updateClients();
    }

    updateText(newText) {
        this.setText(newText);
        return this.update();
    }

    getPos() {
        return this.mPosition;
    }

    destroy() {
        let size_t = FloatingTextList.indexOf(this);
        FloatingTextList.splice(size_t, 1);
        return GMLIB_API.deleteFloatingText(this.mRuntimeId);
    }

    isDynamic() {
        return false;
    }

    static getFloatingText(runtimeId) {
        for (const ft of FloatingTextList) {
            if (ft.getRuntimeId() == runtimeId) {
                if (!ft.isDynamic()) {
                    return ft;
                }
            }
        }
        return null;
    }

    static getAllFloatingTexts() {
        let result = [];
        FloatingTextList.forEach((ft) => {
            if (!ft.isDynamic()) {
                result.push(ft);
            }
        });
        return result;
    }
}

class DynamicFloatingText extends StaticFloatingText {
    constructor(pos, text, updateRate = 1, papi = true) {
        super(pos, text, papi);
        this.mUpdateRate = updateRate;
        this.mTaskId = null;
        this.startUpdate();
    }

    getUpdateRate() {
        return this.mUpdateRate;
    }

    setUpdateRate(updateRate = 1) {
        this.stopUpdate();
        this.mUpdateRate = updateRate;
        this.startUpdate();
    }

    startUpdate() {
        if (this.mTaskId == null) {
            this.mTaskId = setInterval(() => {
                this.update();
            }, this.mUpdateRate * 1000);
            return true;
        }
        return false;
    }

    stopUpdate() {
        if (this.mTaskId != null) {
            clearInterval(this.mTaskId);
            this.mTaskId = null;
            return true;
        }
        return false;
    }

    destroy() {
        let size_t = FloatingTextList.indexOf(this);
        FloatingTextList.splice(size_t, 1);
        return GMLIB_API.deleteFloatingText(this.mRuntimeId);
    }

    isDynamic() {
        return true;
    }

    static getFloatingText(runtimeId) {
        for (const ft of FloatingTextList) {
            if (ft.getRuntimeId() == runtimeId) {
                if (ft.isDynamic()) {
                    return ft;
                }
            }
        }
        return null;
    }

    static getAllFloatingTexts() {
        let result = [];
        FloatingTextList.forEach((ft) => {
            if (ft.isDynamic()) {
                result.push(ft);
            }
        });
        return result;
    }
}

class Minecraft {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

    static getServerAverageTps() {
        return GMLIB_API.getServerAverageTps();
    }

    static getServerCurrentTps() {
        return GMLIB_API.getServerCurrentTps();
    }

    static getServerMspt() {
        return GMLIB_API.getServerMspt();
    }

    static getAllPlayerUuids() {
        return GMLIB_API.getAllPlayerUuids();
    }

    static getPlayerNbt(uuid) {
        let snbt = GMLIB_API.getPlayerNbt(uuid);
        if (snbt == "null") {
            return null;
        }
        let nbt = NBT.parseSNBT(snbt);
        return nbt;
    }

    static setPlayerNbt(uuid, nbt, forceCreate = true) {
        let snbt = nbt.toSNBT();
        return GMLIB_API.setPlayerNbt(uuid, snbt, forceCreate);
    }

    static setPlayerNbtTags(uuid, nbt, tags) {
        let snbt = nbt.toSNBT();
        return GMLIB_API.setPlayerNbtTags(uuid, snbt, tags);
    }

    static getPlayerPosition(uuid) {
        let pos = GMLIB_API.getPlayerPosition(uuid);
        if (pos.dimid == -1) {
            return null;
        }
        return pos;
    }

    static setPlayerPosition(uuid, pos) {
        return GMLIB_API.setPlayerPosition(uuid, pos);
    }

    static getWorldSpawn() {
        return GMLIB_API.getWorldSpawn();
    }

    static setWorldSpawn(pos) {
        return GMLIB_API.setWorldSpawn(pos);
    }

    static getPlayerSpawnPoint() {
        return GMLIB_API.getPlayerSpawnPoint();
    }

    static setPlayerSpawnPoint(pos) {
        GMLIB_API.setPlayerSpawnPoint(pos);
    }

    static clearPlayerSpawnPoint() {
        GMLIB_API.clearPlayerSpawnPoint();
    }

    static setEducationFeatureEnabled() {
        return GMLIB_API.setEducationFeatureEnabled();
    }

    static registerAbilityCommand() {
        return GMLIB_API.registerAbilityCommand();
    }

    static setEnableAchievement() {
        return GMLIB_API.setEnableAchievement();
    }

    static setForceTrustSkins() {
        return GMLIB_API.setForceTrustSkins();
    }

    static enableCoResourcePack() {
        return GMLIB_API.enableCoResourcePack();
    }

    static getWorldName() {
        return GMLIB_API.getLevelName();
    }

    static setWorldName(name) {
        return GMLIB_API.setLevelName(name);
    }

    static setFakeSeed(seed = 114514) {
        return GMLIB_API.setFakeSeed(seed);
    }

    static setUnknownBlockCleaner() {
        return GMLIB_API.setUnknownBlockCleaner();
    }

    static playerToEntity(player) {
        return GMLIB_API.PlayerToEntity(player);
    }

    static spawnEntity(pos, name) {
        return GMLIB_API.spawnEntity(pos, name);
    }

    static shootProjectile(entity, proj, speed = 2, offset = 3) {
        return GMLIB_API.shootProjectile(entity, proj, speed, offset);
    }

    static throwEntity(entity, proj, speed = 2, offset = 3) {
        return GMLIB_API.throwEntity(entity, proj, speed = 2, offset = 3);
    }

    static chooseResourcePackI18nLanguage(language) {
        return GMLIB_API.chooseResourcePackI18nLanguage(language);
    }

    static resourcePackTranslate(key, params = []) {
        return GMLIB_API.resourcePackTranslate(key, params);
    }
}

class Recipes {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

    static registerStoneCutterRecipe(recipeId, inputName, inputAux, outputName, outputAux, outputCount) {
        return GMLIB_API.registerStoneCutterRecipe(recipeId, inputName, inputAux, outputName, outputAux, outputCount);
    }

    static registerSmithingTrimRecipe(recipeId, template, base, addition) {
        return GMLIB_API.registerSmithingTrimRecipe(recipeId, template, base, addition);
    }

    static registerSmithingTransformRecipe(recipeId, template, base, addition, result) {
        return GMLIB_API.registerSmithingTransformRecipe(recipeId, template, base, addition, result);
    }

    static registerBrewingContainerRecipe(recipeId, input, output, reagent) {
        return GMLIB_API.registerBrewingContainerRecipe(recipeId, input, output, reagent);
    }

    static registerBrewingMixRecipe(recipeId, input, output, reagent) {
        return GMLIB_API.registerBrewingMixRecipe(recipeId, input, output, reagent);
    }

    // tags ["furnace", "blast_furnace", "smoker", "campfire", "soul_campfire"]
    static registerFurnaceRecipe(recipeId, input, output, tags = ["furnace"]) {
        return GMLIB_API.registerFurnaceRecipe(recipeId, input, output, tags);
    }

    // unlock : "AlwaysUnlocked", "PlayerHasManyItems", "PlayerInWater", "None", Item ID
    static registerShapedRecipe(recipeId, shape, ingredients, result, count = 1, unlock = "AlwaysUnlocked") {
        return GMLIB_API.registerShapedRecipe(recipeId, shape, ingredients, result, count, unlock);
    }

    static registerShapelessRecipe(recipeId, ingredients, result, count = 1, unlock = "AlwaysUnlocked") {
        return GMLIB_API.registerShapelessRecipe(recipeId, ingredients, result, count, unlock);
    }
}

class Experiments {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

    static getAllExperimentIds() {
        return GMLIB_API.getAllExperiments();
    }

    static getExperimentTranslatedName(id) {
        return GMLIB_API.getExperimentTranslatedName(id);
    }

    static getExperimentsMap() {
        let ids = this.getAllExperimentIds();
        let result = {};
        for (let id in ids) {
            let name = this.getExperimentTranslatedName(id);
            result[id] = name;
        }
        return result;
    }

    static getExperimentEnabled(id) {
        return GMLIB_API.getExperimentEnabled(id);
    }

    static setExperimentEnabled(id, value = true) {
        return GMLIB_API.setExperimentEnabled(id, value);
    }

    static registerExperimentsRequire(id) {
        return GMLIB_API.registerExperimentsRequire(id);
    }
}

class GMLIB {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

    static isVersionMatched(major, minor, patch) {
        return GMLIB_API.isVersionMatched(major, minor, patch);
    }

    static getVersion_LRCA() {
        return GMLIB_API.getVersion_LRCA();
    }

    static getVersion_GMLIB() {
        return GMLIB_API.getVersion_GMLIB();
    }
}

class Scoreboard {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

    // Targets
    static getAllTrackedEntities() {
        return GMLIB_API.getAllScoreboardEntities();
    }

    static getAllTrackedPlayers() {
        return GMLIB_API.getAllScoreboardPlayers();
    }

    static getAllTrackedFakePlayers() {
        return GMLIB_API.getAllScoreboardFakePlayers();
    }

    static getAllTrackedTargets() {
        let result = [];
        GMLIB_API.getAllScoreboardPlayers().forEach((uuid) => {
            let key = {
                "Type": "Player",
                "Uuid": uuid
            };
            result.push(key);
        });
        GMLIB_API.getAllScoreboardEntities().forEach((uniqueId) => {
            let key = {
                "Type": "Entity",
                "UniqueId": uniqueId
            };
            result.push(key);
        });
        GMLIB_API.getAllScoreboardFakePlayers().forEach((name) => {
            let key = {
                "Type": "FakePlayer",
                "Name": name
            };
            result.push(key);
        });
        return result;
    }

    // Objectives
    static addObjective(name, displayName = "") {
        if (displayName == "") {
            return GMLIB_API.addObjective(name);
        }
        return GMLIB_API.addObjectiveWithDisplayName(name, displayName);
    }

    static removeObjective(name) {
        return GMLIB_API.removeObjective(name);
    }

    static getAllObjectives() {
        return GMLIB_API.getAllObjectives();
    }

    static getDisplayName(objective) {
        return GMLIB_API.getDisplayName(objective);
    }

    static setDisplayName(objective, displayName) {
        return GMLIB_API.setDisplayName(objective, displayName);
    }

    static setDisplay(objective, slot, order = 0) {
        GMLIB_API.setDisplayObjective(objective, slot, order);
    }

    static clearDisplay(slot) {
        GMLIB_API.clearDisplayObjective(slot);
    }

    // Player Score
    static getPlayerScore(uuid, objective) {
        if (GMLIB_API.playerHasScore(uuid, objective)) {
            return GMLIB_API.getPlayerScore(uuid, objective);
        }
        return null;
    }

    static addPlayerScore(uuid, objective, value) {
        return GMLIB_API.addPlayerScore(uuid, objective, value);
    }

    static reducePlayerScore(uuid, objective, value) {
        return GMLIB_API.reducePlayerScore(uuid, objective, value);
    }

    static setPlayerScore(uuid, objective, value) {
        return GMLIB_API.setPlayerScore(uuid, objective, value);
    }

    static resetPlayerScore(uuid, objective) {
        return GMLIB_API.resetPlayerScore(uuid, objective);
    }

    static resetPlayerScores(uuid) {
        return GMLIB_API.resetPlayerScores(uuid);
    }

    // FakePlayer Score
    static getFakePlayerScore(name, objective) {
        if (GMLIB_API.fakePlayerHasScore(name, objective)) {
            return GMLIB_API.getFakePlayerScore(name, objective);
        }
        return null;
    }

    static addFakePlayerScore(name, objective, value) {
        return GMLIB_API.addFakePlayerScore(name, objective, value);
    }

    static reduceFakePlayerScore(name, objective, value) {
        return GMLIB_API.reduceFakePlayerScore(name, objective, value);
    }

    static setFakePlayerScore(name, objective, value) {
        return GMLIB_API.setFakePlayerScore(name, objective, value);
    }

    static resetFakePlayerScore(name, objective) {
        return GMLIB_API.resetFakePlayerScore(name, objective);
    }

    static resetFakePlayerScores(name) {
        return GMLIB_API.resetFakePlayerScores(name);
    }

    // Entity Score
    static getEntityScore(uniqueId, objective) {
        if (GMLIB_API.entityHasScore(uniqueId, objective)) {
            return GMLIB_API.getEntityScore(uniqueId, objective);
        }
        return null;
    }

    static addEntityScore(uniqueId, objective, value) {
        return GMLIB_API.addEntityScore(uniqueId, objective, value);
    }

    static reduceEntityScore(uniqueId, objective, value) {
        return GMLIB_API.reduceEntityScore(uniqueId, objective, value);
    }

    static setEntityScore(uniqueId, objective, value) {
        return GMLIB_API.setEntityScore(uniqueId, objective, value);
    }

    static resetEntityScore(uniqueId, objective) {
        return GMLIB_API.resetEntityScore(uniqueId, objective);
    }

    static resetEntityScores(uniqueId) {
        return GMLIB_API.resetEntityScores(uniqueId);
    }

}

class JsonConfig {
    constructor(path, defultValue = {}) {
        this.mData = defultValue;
        this.mPath = path;
    }

    init() {
        if (File.exists(this.mPath)) {
            let existDataStr = File.readFrom(this.mPath);
            this.mData = Object.assign({}, this.mData, JSON.parse(existDataStr));
        }
        this.save();
    }

    save(format = 4) {
        let dataStr = JSON.stringify(this.mData, null, format);
        File.writeTo(this.mPath, dataStr);
    }

    getData() {
        return this.mData;
    }

    get(key, defultValue = null) {
        let result = this.getData()[key];
        if (!result && defultValue != null) {
            this.set(key, defultValue);
            return defultValue;
        }
        return result;
    }

    set(key, value) {
        this.getData()[key] = value;
        this.save();
    }

    delete(key) {
        delete this.getData()[key];
        this.save();
    }
}

module.exports = {
    StaticFloatingText,
    DynamicFloatingText,
    Minecraft,
    Recipes,
    Experiments,
    GMLIB,
    Scoreboard,
    JsonConfig
};