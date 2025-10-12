/// <reference path='d:/dts/dts/helperlib/src/index.d.ts'/> 

const getPluginName = () => {
    if (getPluginName.PluginNameCache) return getPluginName.PluginNameCache;

    return getPluginName.PluginNameCache = (() => {
        if (ll.getCurrentPluginInfo) return ll.getCurrentPluginInfo().name;

        const error = new Error("getPluginName");
        switch (ll.scriptEngineVersion) {
            case "QuickJS": {
                if (!error.stack) break;
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
                break;
            }
            case "V8 12.4.254.21-node.21": {
                try {
                    const selfFileName = require('path').basename(__filename);
                    const pluginDirectory = Object.entries(
                        require('module')._pathCache
                    ).find(
                        ([key, _]) => key.includes(selfFileName)
                    )[0].split("\u0000")[1];
                    const directories = pluginDirectory.split("\\");
                    const pluginName = directories[directories.findIndex(value => value === "plugins") + 1].trim();
                    if (pluginName) return pluginName;
                } catch { }

                if (!error.stack) break;
                const /** @type {string} */ line = error.stack.trim().split("\n").pop().trim();
                if (line.includes(".js") && /:\d+:\d+$/.test(line)) {
                    const directories = line.split("\\");
                    const pluginName = directories[directories.findIndex(value => value === "plugins") + 1].trim();
                    if (pluginName) return pluginName;
                }
                break;
            }
            default: break;
        }
        return "Unknown";
    })();
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