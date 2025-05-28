/// <reference path='d:/dts/dts/helperlib/src/index.d.ts'/> 

const getPluginName = () => {
    // quickjs
    try {
        throw new Error("getPluginName");
    } catch (error) {
        const /** @type {string} */ line = error.stack.trim().split("\n").pop().trim();
        if (line.includes("<anonymous>")) {
            return line.slice(
                line.indexOf("(") + 1,
                line.indexOf("\\")
            );
        }
        if (line.includes("<eval>")) {
            return line.slice(
                line.indexOf("/", line.indexOf("/") + 1) + 1,
                line.indexOf("\\")
            );
        }
    }

    // nodejs
    try {
        const path = require('path');
        const selfFileName = path.basename(__filename);
        const pluginDirectory = Object.entries(
            require('module')._pathCache
        ).find(
            ([key, _]) =>
                key.includes(selfFileName)
        )[0].split("\u0000")[1];
        const directories = pluginDirectory.split("\\");
        const pluginName = directories[directories.findIndex(value => value === "plugins") + 1].trim();
        if (pluginName) return pluginName;
    } catch { }
    try {
        throw new Error("getPluginName");
    } catch (error) {
        const /** @type {string} */ line = error.stack.trim().split("\n").pop().trim();
        if (line.includes(".js") && /:\d+:\d+$/.test(line)) {
            const directories = line.split("\\");
            const pluginName = directories[directories.findIndex(value => value === "plugins") + 1].trim();
            if (pluginName) return pluginName;
        }
    }
    return "Unknown";
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
            ? ll.importss("PlaceholderAPI", "translateFromActor")(value, actor, language)
            : ll.importss("PlaceholderAPI", "translate")(value, language);
    },
    registerPlaceholder(placeholder, callback) {
        const pluginName = getPluginName();
        ll.exports((...args) => {
            if(!args[0].uniqueId) args[0] = undefined;
            return callback(...args) ?? "<std::nullopt>";
        }, pluginName, callback.getName());
        ll.importss("PlaceholderAPI", "registerPlaceholder")(placeholder, callback.getName(), pluginName);
    },
    unregisterPlaceholder(placeholder) {
        return ll.importss("PlaceholderAPI", "unregisterPlaceholder")(placeholder);
    },
    unregisterPlaceholderFromModName(placeholder) {
        return ll.importss("PlaceholderAPI", "unregisterPlaceholderFromModName")(placeholder);
    },
    getValue(placeholder, actor = undefined, params = {}, language = "") {
        if (actor instanceof LLSE_Player) actor = ll.imports("GMLib_ServerAPI", "PlayerToEntity")(actor);
        const result = actor instanceof LLSE_Entity
            ? ll.importss("PlaceholderAPI", "getValueFromActor")(placeholder, actor, params, language)
            : ll.importss("PlaceholderAPI", "getValue")(placeholder, params, language);
        return result !== "<std::nullopt>" ? result : undefined;
    }
};