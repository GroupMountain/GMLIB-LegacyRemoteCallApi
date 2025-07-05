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
        }, pluginName, `Placeholder_${placeholder}`);
        ll.imports("PlaceholderAPI", "registerPlaceholder")(placeholder, `Placeholder_${placeholder}`, pluginName);
    },
    unregisterPlaceholder(placeholder) {
        return ll.imports("PlaceholderAPI", "unregisterPlaceholder")(placeholder);
    },
    unregisterPlaceholderFromModName(placeholder) {
        return ll.imports("PlaceholderAPI", "unregisterPlaceholderFromModName")(placeholder);
    },
    getValue(placeholder, actor = undefined, params = {}, language = "") {
        if (actor instanceof LLSE_Player) actor = ll.imports("GMLib_ServerAPI", "PlayerToEntity")(actor);
        const result = actor instanceof LLSE_Entity
            ? ll.imports("PlaceholderAPI", "getValueFromActor")(placeholder, actor, params, language)
            : ll.imports("PlaceholderAPI", "getValue")(placeholder, params, language);
        return result !== "<std::nullopt>" ? result : undefined;
    }
};