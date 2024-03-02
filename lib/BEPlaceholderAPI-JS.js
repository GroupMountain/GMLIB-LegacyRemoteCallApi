const PlaceholderAPI = {
    getValueAPI: ll.import("BEPlaceholderAPI", "GetValue"),
    getValueByPlayerAPI: ll.import("BEPlaceholderAPI", "GetValueWithPlayer"),
    registerPlayerPlaceholderAPI: ll.import("BEPlaceholderAPI", "registerPlayerPlaceholder"),
    registerServerPlaceholderAPI: ll.import("BEPlaceholderAPI", "registerServerPlaceholder"),
    registerStaticPlaceholderAPI: ll.import("BEPlaceholderAPI", "registerStaticPlaceholder"),
    translateStringAPI: ll.import("BEPlaceholderAPI", "translateString"),
    translateStringWithPlayerAPI: ll.import("BEPlaceholderAPI", "translateStringWithPlayer"),
    unRegisterPlaceholderAPI: ll.import("BEPlaceholderAPI", "unRegisterPlaceholder"),
    getAllPAPI: ll.import("BEPlaceholderAPI", "getAllPAPI")
}

Function.prototype.getName = function () {
    return this.name || this.toString().match(/function\s*([^(]*)\(/)[1]
}

class PAPI {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

    static registerPlayerPlaceholder(func, PluginName, PAPIName) {
        ll.export(func, PluginName, func.getName());
        PlaceholderAPI.registerPlayerPlaceholderAPI(PluginName, func.getName(), PAPIName);
    }

    static registerServerPlaceholder(func, PluginName, PAPIName) {
        ll.export(func, PluginName, func.getName());
        PlaceholderAPI.registerServerPlaceholderAPI(PluginName, func.getName(), PAPIName);
    }

    static registerStaticPlaceholder(func, PluginName, PAPIName, UpdateInterval = 50) {
        ll.export(func, PluginName, func.getName());
        PlaceholderAPI.registerStaticPlaceholderAPI(PluginName, func.getName(), PAPIName, UpdateInterval);
    }

    static getValue(key) {
        return PlaceholderAPI.getValueAPI(key);
    }

    static getValueByPlayer(key, pl) {
        return PlaceholderAPI.getValueByPlayerAPI(key, pl);
    }

    static translateString(str, pl = null) {
        if (pl) {
            return PlaceholderAPI.translateStringWithPlayerAPI(str, pl);
        }
        return PlaceholderAPI.translateStringAPI(str);
    }

    static unRegisterPlaceholder(str) {
        return PlaceholderAPI.unRegisterPlaceholderAPI(str);
    }

    static getAllPAPI() {
        return PlaceholderAPI.getAllPAPI();
    }

}

module.exports = {
    PAPI
};