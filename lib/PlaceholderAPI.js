/// <reference path='d:/dts/dts/helperlib/src/index.d.ts'/> 

const getPluginName = () => {
    try {
        throw new Error("getPluginName");
    } catch (error) {
        return error.stack.trim().match(/plugins\\(.*)\\.*\.js:[0-9]+\)$/i)?.[1]
            || error.stack.trim().match(/at <anonymous> \(([^\\|/]+)(.*?):\d+:\d+\)$/i)?.[1]
            || "Unknown";
    }
};

Function.prototype.getName =
    /**
     * 获取函数名字
     * @returns {string}
     */
    function () {
        return this.name || this.toString().match(/function\s*([^(]*)\(/)?.[1] || getStringHashCode(this.toString()).toString(16);
    };

/**
 * 获取字符串哈希值
 * @param {string} str 字符串
 * @returns {number}
 */
function getStringHashCode(str) {
    let hash = 0, chr;
    if (str.length === 0) return hash;
    for (let i = 0; i < str.length; i++) {
        chr = str.charCodeAt(i);
        hash = ((hash << 5) - hash) + chr;
        hash |= 0;
    }
    return hash;
}

module.exports = {
    translate(value, actor = undefined, language = "") {
        return actor instanceof LLSE_Entity
            ? ll.imports("PlaceholderAPI", "translateFromActor")(value, actor, language)
            : ll.imports("PlaceholderAPI", "translate")(value, language);
    },
    registerPlaceholder(placeholder, callback) {
        const pluginName = getPluginName();
        ll.exports((...args) => {
            if(!args[0].uniqueId) args[0] = undefined;
            return callback(...args) ?? "<std::nullopt>";
        }, pluginName, callback.getName());
        ll.imports("PlaceholderAPI", "registerPlaceholder")(placeholder, callback.getName(), pluginName);
    },
    unregisterPlaceholder(placeholder) {
        return ll.imports("PlaceholderAPI", "unregisterPlaceholder")(placeholder);
    },
    unregisterPlaceholderFromModName(placeholder) {
        return ll.imports("PlaceholderAPI", "unregisterPlaceholderFromModName")(placeholder);
    },
    getValue(placeholder, actor = undefined, params = {}, language = "") {
        if (actor instanceof LLSE_Player) actor = ll.import("GMLib_ServerAPI", "PlayerToEntity")(actor);
        const result = actor instanceof LLSE_Entity
            ? ll.imports("PlaceholderAPI", "getValueFromActor")(placeholder, actor, params, language)
            : ll.imports("PlaceholderAPI", "getValue")(placeholder, params, language);
        return result !== "<std::nullopt>" ? result : undefined;
    }
};