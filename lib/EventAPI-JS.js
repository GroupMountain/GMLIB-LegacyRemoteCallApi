/** 事件创建函数 @type {function(string,string):boolean} */
const CallEvent = ll.import("GMLIB_API", "callCustomEvent");

/** 事件ID @type {number} */
let NextEventId = 0;

/**
 * 获取事件ID标识名
 * @returns {string} 事件ID标识名
 */
function getNextEventId() {
    NextEventId++;
    return "GMLIB_Event_" + NextEventId;
}

/** 事件类 */
class Event {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

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
            logger.error(`Cannot listen event "${event}"!`);
            logger.error(`Event "${event}" No Found!`);
        }
        return result;
    }
}

module.exports = {
    Event
};