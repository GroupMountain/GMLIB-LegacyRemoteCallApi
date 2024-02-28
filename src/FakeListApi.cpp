#include "Global.h"
void Export_Legacy_GMLib_FakeListAPI() {
    // 获取所有假名字
    RemoteCall::exportAs("GMLib_FakeListAPI", "getAllFakeNames", []() -> std::vector<std::string> {
        return GMLIB::Server::FakeList::getAllFakeNames();
    });
    // 添加假名字
    RemoteCall::exportAs(
        "GMLib_FakeListAPI",
        "addFakeList",
        [](const std::string& name,const std::string& xuid) -> bool { return GMLIB::Server::FakeList::addFakeList(name, xuid, ActorUniqueID(-1), mce::UUID::random()); }
    );

    // 移除假名字
    RemoteCall::exportAs("GMLib_FakeListAPI", "removeFakeList", [](const std::string& nameOrXuid) -> bool {
        return GMLIB::Server::FakeList::removeFakeList(nameOrXuid);
    });

    // 移除所有假名字
    RemoteCall::exportAs("GMLib_FakeListAPI", "removeAllFakeLists", []() {
        GMLIB::Server::FakeList::removeAllFakeLists();
    });

    // 检查假名字是否存在
    RemoteCall::exportAs("GMLib_FakeListAPI", "checkFakeListExistsName", [](const std::string& name) -> bool {
        return GMLIB::Server::FakeList::checkFakeListExistsName(name);
    });

    // 检查假名字和XUID是否存在
    RemoteCall::exportAs(
        "GMLib_FakeListAPI",
        "checkFakeListExists",
        [](const std::string& name, const std::string& xuid) -> bool {
            return GMLIB::Server::FakeList::checkFakeListExists(name, xuid);
        }
    );

    // 设置真实名字和假名字对应关系
    RemoteCall::exportAs(
        "GMLib_FakeListAPI",
        "setListName",
        [](const std::string& realName, const std::string& fakeName) {
            GMLIB::Server::FakeList::setListName(realName, fakeName);
        }
    );

    // 重置真实名字和假名字对应关系
    RemoteCall::exportAs("GMLib_FakeListAPI", "resetListName", [](const std::string& realName) {
        GMLIB::Server::FakeList::resetListName(realName);
    });

    // 设置模拟玩家列表优化状态
    RemoteCall::exportAs("GMLib_FakeListAPI", "setSimulatedPlayerListOptimizeEnabled", [](bool value) {
        GMLIB::Server::FakeList::setSimulatedPlayerListOptimizeEnabled(value);
    });

    // 获取模拟玩家列表优化状态
    RemoteCall::exportAs("GMLib_FakeListAPI", "getSimulatedPlayerListOptimizeEnabled", []() -> bool {
        return GMLIB::Server::FakeList::getSimulatedPlayerListOptimizeEnabled();
    });
}