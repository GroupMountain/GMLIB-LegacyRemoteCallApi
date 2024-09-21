/** 事件创建函数 @type {function(string,string):boolean} */
const CallEvent = ll.import("GMLIB_Event_API", "callCustomEvent");
/** 获取事件ID函数 @type {function():string} */
const getNextEventId = ll.import("GMLIB_Event_API", "getNextScriptEventId");

/** 事件类 */
class Event {
    constructor() { throw new Error("Static class cannot be instantiated"); }

    /**
     * 监听事件
     * @param {string} event 事件名称
     * @param {function} callback 回调
     * @returns {boolean} 是否创建成功
     */
    static listen(event, callback) {
        let eventId = getNextEventId();
        ll.export(callback, event, eventId);
        let result = CallEvent(event, eventId);
        if (!result) {
            logger.error(`Cannot listen event "${event}" !`);
            logger.error(`GMLIB Script Event "${event}" does not exist !`);
        }
        return result;
    }
}

module.exports = { Event };