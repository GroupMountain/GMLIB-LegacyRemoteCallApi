const CallEvent = ll.import("GMLIB_API", "callCustomEvent");

let NextEventId = 0;

function getNextEventId() {
    NextEventId++;
    return "GMLIB_Event_" + NextEventId;
}

class Event {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

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