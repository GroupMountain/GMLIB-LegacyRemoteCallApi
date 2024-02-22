const PAPIgetValueAPI = ll.import("BEPlaceholderAPI", "GetValue")
const PAPIgetValueByPlayerAPI = ll.import("BEPlaceholderAPI", "GetValueWithPlayer")
const PAPIregisterPlayerPlaceholderAPI = ll.import("BEPlaceholderAPI", "registerPlayerPlaceholder")
const PAPIregisterServerPlaceholderAPI = ll.import("BEPlaceholderAPI", "registerServerPlaceholder")
const PAPIregisterStaticPlaceholderAPI = ll.import("BEPlaceholderAPI", "registerStaticPlaceholder")
const PAPItranslateStringAPI = ll.import("BEPlaceholderAPI", "translateString")
const PAPIunRegisterPlaceholderAPI = ll.import("BEPlaceholderAPI", "unRegisterPlaceholder")

Function.prototype.getName = function () {

    return this.name || this.toString().match(/function\s*([^(]*)\(/)[1]

}

class PAPI {
    constructor() { }

    static registerPlayerPlaceholder(func, PluginName, PAPIName) {

        ll.export(func, PluginName, func.getName())
        PAPIregisterPlayerPlaceholderAPI(PluginName, func.getName(), PAPIName)
    }

    static registerServerPlaceholder(func, PluginName, PAPIName) {
        ll.export(func, PluginName, func.getName())
        PAPIregisterServerPlaceholderAPI(PluginName, func.getName(), PAPIName)
    }

    static registerStaticPlaceholder(func, PluginName, PAPIName, UpdateInterval = 50) {
        ll.export(func, PluginName, func.getName())
        PAPIregisterStaticPlaceholderAPI(PluginName, func.getName(), PAPIName, UpdateInterval)
    }

    static getValue(key) {
        return PAPIgetValueAPI(key)
    }

    static getValueByPlayer(key, xuid) {
        return PAPIgetValueByPlayerAPI(key, xuid)
    }

    static translateString(str, xuid = "") {
        return PAPItranslateStringAPI(str, xuid)
    }

    static unRegisterPlaceholder(str) {
        return PAPIunRegisterPlaceholderAPI(str)
    }

}

module.exports = {
    PAPI
};