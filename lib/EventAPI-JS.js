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
    Event: {
        /**
         * 事件订阅记录   
         * 例如: {事件名: [事件ID, ...], ...}
         * @type {Object.<string, number[]>}
         */
        mEventData: {},
        /**
         * 事件异常处理回调
         * @param {Error} error
         * @param {string} eventName
         * @param {number} eventID
         * @param {string} pluginName
         * @returns {void}
         */
        mErrorHanlerCallback: (error, eventName, eventID, pluginName) => {
            logger.error(`Info: ${pluginName}-${eventName}-${eventID}   Exception: ${error.message}\n${error.stack}`);
        },

        /**
         * 监听事件(兼容旧版)
         * @param {string} eventName
         * @param {function} callback
         * @param {boolean}
         */
        listen: function (eventName, callback) {
            try {
                if (typeof callback !== "function") return false;
                const eventReflection = {
                    onServerStopping: "ll::ServerStoppingEvent",
                    onClientLogin: "gmlib::ClientLoginAfterEvent",
                    onWeatherChange: "gmlib::WeatherUpdateBeforeEvent",
                    onMobPick: "gmlib::MobPickupItemBeforeEvent",
                    onItemTrySpawn: "gmlib::ItemActorSpawnBeforeEvent",
                    onItemSpawned: "gmlib::ItemActorSpawnAfterEvent",
                    onEntityTryChangeDim: "gmlib::ActorChangeDimensionBeforeEvent",
                    onLeaveBed: "gmlib::PlayerStopSleepBeforeEvent",
                    onDeathMessage: "gmlib::DeathMessageAfterEvent",
                    onMobHurted: "gmlib::MobHurtAfterEvent",
                    onEndermanTake: "gmlib::EndermanTakeBlockBeforeEvent",
                    onEntityChangeDim: "gmlib::ActorChangeDimensionAfterEvent",
                    onDragonRespawn: "gmlib::DragonRespawnBeforeEvent",
                    onProjectileTryCreate: "gmlib::ProjectileCreateBeforeEvent",
                    onProjectileCreate: "gmlib::ProjectileCreateAfterEvent",
                    onSpawnWanderingTrader: "gmlib::SpawnWanderingTraderBeforeEvent",
                    onHandleRequestAction: "gmlib::HandleRequestActionBeforeEvent",
                    onSendContainerClosePacket: "gmlib::ContainerClosePacketSendAfterEvent"
                };
                this.emplaceListener(eventReflection[eventName] ?? eventName, event => {
                    const result = callback(...event.params);
                    if (typeof (result) === "boolean" && !result) event.cancel();
                });
                return true;
            } catch { }
            return false;
        },

        /**
         * 订阅事件
         * @param {string} eventName
         * @param {function} callback
         * @param {number?} priority
         * @param {string?} pluginName
         * @returns {number}
         */
        emplaceListener: function (eventName, callback, priority = this.EventPriority.Normal, pluginName = getPluginName()) {
            if (typeof callback !== "function") throw new Error("callback must be a function!");
            const /** @type {number} */ eventId = ll.imports("GMLIB_Event_API", "emplaceListener")(pluginName, eventName, priority);
            if (eventId === -1) throw new Error(`Event ${eventName} creation failed!`);
            ll.exports((...data) => {
                let /** @type {boolean} */ result = typeof (data.slice(-1)[0]) === "boolean" ? data.pop() : false;
                try {
                    callback({
                        params: data,
                        cancel: () => result = true,
                        setCancelled: (/** @type {boolean} */value) => { result = value; },
                        isCancelled: () => result,
                        getId: () => eventId,
                        getEventType: () => eventName
                    });
                } catch (error) {
                    try {
                        this.mErrorHanlerCallback(error, eventName, eventId, pluginName);
                    } catch { }
                }
                return result;
            }, pluginName, eventName + "_" + eventId);
            (this.mEventData[eventName] ??= []).push(eventId);
            return eventId;
        },

        /**
         * 取消事件订阅
         * @param {number} eventId
         * @param {boolean}
         */
        removeListener: function (eventId) {
            const result = ll.imports("GMLIB_Event_API", "removeListener")(eventId);
            if (result) {
                for (let [eventName, eventIds] of Object.entries(this.mEventData)) {
                    this.mEventData[eventName] = eventIds.filter(id => id !== eventId);
                    if (this.mEventData[eventName].length === 0) delete this.mEventData[eventName];
                }
            }
            return result;
        },

        /**
         * 判断事件订阅是否存在
         * @param {number} eventId
         * @returns {boolean}
         */
        hasListener: function (eventId) {
            return ll.imports("GMLIB_Event_API", "hasListener")(eventId);
        },

        /**
         * 获取订阅事件优先级
         * @param {number} eventId
         * @returns {number?}
         */
        getListenerPriority: function (eventId) {
            const priority = ll.imports("GMLIB_Event_API", "getListenerPriority")(eventId);
            return priority === -1 ? undefined : priority;
        },

        /**
         * 获取订阅事件列表
         * @param {string | undefined} eventName
         * @returns {number[] | Object.<string, number[]>}
         */
        getListener: function (eventName) {
            return eventName === undefined ? this.mEventData : this.mEventData[eventName] ?? [];
        },

        /**
         * 设置异常处理回调
         * @param {function(Error, string, number, string): void} callback
         * @returns {boolean}
         */
        setErrorHanlerCallback: function (callback) {
            if (callback === undefined || typeof callback !== "function") return false;
            this.mErrorHanlerCallback = callback;
            return true;
        },

        /**
         * 事件优先级
         */
        EventPriority: {
            Highest: 0,
            High: 100,
            Normal: 200,
            Low: 300,
            Lowest: 400
        }
    }
};