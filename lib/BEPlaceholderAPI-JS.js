const PlaceholderAPI = {
    /** 获取一个服务器变量的值 @type {function(string):string} */
    getValueAPI: ll.imports("BEPlaceholderAPI", "GetValue"),
    /** 获取一个玩家变量的值 @type {function(string,Player):string} */
    getValueByPlayerAPI: ll.imports("BEPlaceholderAPI", "GetValueWithPlayer"),
    /** 注册一个玩家变量 @type {function(string,string,string):boolean} */
    registerPlayerPlaceholderAPI: ll.imports("BEPlaceholderAPI", "registerPlayerPlaceholder"),
    /** 注册一个服务器变量 @type {function(string,string,string):boolean} */
    registerServerPlaceholderAPI: ll.imports("BEPlaceholderAPI", "registerServerPlaceholder"),
    /** 注册一个静态变量 @type {function(string,string,string,number):boolean} */
    registerStaticPlaceholderAPI: ll.imports("BEPlaceholderAPI", "registerStaticPlaceholder"),
    /** 翻译包含PAPI服务器变量的字符串 @type {function(string):string} */
    translateStringAPI: ll.imports("BEPlaceholderAPI", "translateString"),
    /** 翻译包含PAPI玩家变量的字符串 @type {function(string,Player):string} */
    translateStringWithPlayerAPI: ll.imports("BEPlaceholderAPI", "translateStringWithPlayer"),
    /** 注销PAPI变量 @type {function(string):boolean} */
    unRegisterPlaceholderAPI: ll.imports("BEPlaceholderAPI", "unRegisterPlaceholder"),
    /** 获取所有已注册的PAPI变量 @type {function():Array.<string>} */
    getAllPAPI: ll.imports("BEPlaceholderAPI", "getAllPAPI")
}

/** PAPI变量类 */
class PAPI {
    constructor() {
        throw new Error("Static class cannot be instantiated");
    }

    /**
     * 注册一个玩家PAPI变量
     * @param {function} func 变量调用的函数
     * @param {string} PluginName 插件名字
     * @param {string} PAPIName PAPI变量名
     * @returns {boolean} 是否注册成功
     */
    static registerPlayerPlaceholder(func, PluginName, PAPIName) {
        ll.export(func, PluginName, `Placeholder_${PAPIName}`);
        PlaceholderAPI.registerPlayerPlaceholderAPI(PluginName, `Placeholder_${PAPIName}`, PAPIName);
    }

    /**
     * 注册一个服务器PAPI变量
     * @param {function} func 变量调用的函数
     * @param {string} PluginName 插件名字
     * @param {string} PAPIName PAPI变量名
     * @returns {boolean} 是否注册成功
     */
    static registerServerPlaceholder(func, PluginName, PAPIName) {
        ll.export(func, PluginName, `Placeholder_${PAPIName}`);
        PlaceholderAPI.registerServerPlaceholderAPI(PluginName, `Placeholder_${PAPIName}`, PAPIName);
    }

    /**
     * 注册一个静态PAPI变量
     * @param {function} func 变量调用的函数
     * @param {string} PluginName 插件名字
     * @param {string} PAPIName PAPI变量名
     * @param {number} [UpdateInterval=50] 更新间隔
     * @returns {boolean} 是否注册成功
     */
    static registerStaticPlaceholder(func, PluginName, PAPIName, UpdateInterval = 50) {
        ll.export(func, PluginName, `Placeholder_${PAPIName}`);
        PlaceholderAPI.registerStaticPlaceholderAPI(PluginName, `Placeholder_${PAPIName}`, PAPIName, UpdateInterval);
    }

    /**
     * 获取一个服务器变量的值
     * @param {string} key PAPI变量名
     * @returns {string} 值
     */
    static getValue(key) {
        return PlaceholderAPI.getValueAPI(key);
    }

    /**
     * 获取一个玩家变量的值
     * @param {string} key PAPI变量名
     * @param {Player} pl 玩家对象
     * @returns {string} 值
     */
    static getValueByPlayer(key, pl) {
        return PlaceholderAPI.getValueByPlayerAPI(key, pl);
    }

    /**
     * 翻译带PAPI变量的字符串
     * @param {string} str 字符串
     * @param {Player} pl 玩家对象
     * @returns {string} 翻译结果
     */
    static translateString(str, pl = null) {
        if (pl) {
            return PlaceholderAPI.translateStringWithPlayerAPI(str, pl);
        }
        return PlaceholderAPI.translateStringAPI(str);
    }

    /**
     * 注销一个PAPI变量
     * @param {string} str PAPI变量名
     * @returns {boolean} 是否注销成功
     */
    static unRegisterPlaceholder(str) {
        return PlaceholderAPI.unRegisterPlaceholderAPI(str);
    }

    /**
     * 获取所有已注册的PAPI变量
     * @returns {Array.<string>} 已注册的PAPI变量数组
     */
    static getAllPAPI() {
        return PlaceholderAPI.getAllPAPI();
    }

}

module.exports = {
    PAPI
};