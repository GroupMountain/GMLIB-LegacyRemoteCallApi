/**
 * 
 * @name GMLIB_LRCA-Plugin-Template
 * @brief plugin template for GMLIB-LegacyRemoteCallApi
 * 
 * @copyright Copyright (c) 2024 GroupMountain
 * GMLIB-LegacyRemoteCallApi <https://github.com/GroupMountain/GMLIB-LegacyRemoteCallApi/>
 * 
 */

const PluginInfo = {
    Name: "GMLIB_LRCA-Plugin-Template",
    Author: "your name",
    Version: "0.0.1"
}

// 导入 API
const { JsonConfig, JsonI18n } = require('./GMLIB-LegacyRemoteCallApi/lib/GMLIB_API-JS');

// 默认配置文件
const defaultConfig = {
    "language": "zh_CN"
};

// 默认语言文件
const zh_CN = {
    "consolelog.loaded": "加载成功！",
    "consolelog.info": "插件作者: {1}, 当前版本: v{2}"
};

// 初始化配置文件
const config = new JsonConfig(`./plugins/${PluginInfo.Name}/config/config.json`, defaultConfig);

// 初始化 I18n
const I18n = new JsonI18n(`./plugins/${PluginInfo.Name}/language/`, config.get("language"));
I18n.loadLanguage("zh_CN", zh_CN);    // 升级语言文件
I18n.setDefaultLanguage("zh_CN");     // 设置I18n无法翻译时采用的默认语言

// I18n快捷翻译函数
function tr(key, data = []) {
    return I18n.translate(key, data);
}

// 监听服务器启动
// 在无特殊说明的情况下，一切 MCAPI 都应该在服务器启动后访问。
mc.listen("onServerStarted", () => {
    // 你的代码


    // 打印插件信息
    logger.info(tr("consolelog.loaded"));
    logger.info(tr("consolelog.info", [PluginInfo.Author, PluginInfo.Version]));
});