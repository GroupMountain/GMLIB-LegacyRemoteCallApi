#include "Global.h"
void Export_GMLib_FakeListAPI() {
    // 获取所有虚拟在线玩家
    RemoteCall::exportAs("GMLIB_API", "getAllFakeNames", []() -> std::vector<std::string> {
        return GMLIB::Server::FakeList::getAllFakeNames();
    });
    // 添加虚拟在线玩家
    RemoteCall::exportAs(
        "GMLIB_API",
        "addFakeList",
        [](const std::string& name,const std::string& xuid) -> bool { return GMLIB::Server::FakeList::addFakeList(name, xuid, ActorUniqueID(-1), mce::UUID::random()); }
    );

    // 移除虚拟在线玩家
    RemoteCall::exportAs("GMLIB_API", "removeFakeList", [](const std::string& nameOrXuid) -> bool {
        return GMLIB::Server::FakeList::removeFakeList(nameOrXuid);
    });

    // 移除所有虚拟在线玩家
    RemoteCall::exportAs("GMLIB_API", "removeAllFakeLists", []() {
        GMLIB::Server::FakeList::removeAllFakeLists();
    });

    // 检查虚拟在线玩家是否存在
    RemoteCall::exportAs("GMLIB_API", "checkFakeListExistsName", [](const std::string& name) -> bool {
        return GMLIB::Server::FakeList::checkFakeListExistsName(name);
    });

    // 检查虚拟在线玩家和XUID是否存在
    RemoteCall::exportAs(
        "GMLIB_API",
        "checkFakeListExists",
        [](const std::string& name, const std::string& xuid) -> bool {
            return GMLIB::Server::FakeList::checkFakeListExists(name, xuid);
        }
    );

    // 设置真实名字和虚拟在线玩家对应关系
    RemoteCall::exportAs(
        "GMLIB_API",
        "setListName",
        [](const std::string& realName, const std::string& fakeName) {
            GMLIB::Server::FakeList::setListName(realName, fakeName);
        }
    );

    // 重置真实名字和虚拟在线玩家对应关系
    RemoteCall::exportAs("GMLIB_API", "resetListName", [](const std::string& realName) {
        GMLIB::Server::FakeList::resetListName(realName);
    });

    // 设置模拟玩家列表优化状态
    RemoteCall::exportAs("GMLIB_API", "setSimulatedPlayerListOptimizeEnabled", [](bool value) {
        GMLIB::Server::FakeList::setSimulatedPlayerListOptimizeEnabled(value);
    });

    // 获取模拟玩家列表优化状态
    RemoteCall::exportAs("GMLIB_API", "getSimulatedPlayerListOptimizeEnabled", []() -> bool {
        return GMLIB::Server::FakeList::getSimulatedPlayerListOptimizeEnabled();
    });
}