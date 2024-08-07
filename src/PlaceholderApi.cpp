#include "Global.h"
#include <regex>

namespace PAPIRemoteCall {

std::string removeBrackets(std::string a1) {
    a1.erase(a1.find_last_not_of("%") + 1);
    return a1;
}

bool isParameters(std::string const& str) {
    std::regex reg("[<]([^<>]+)[>]");
    return std::regex_search(removeBrackets(str), reg);
}

std::string GetValue(std::string const& from) { return PlaceholderAPI::getValue(from); }

std::string GetValueWithPlayer(std::string const& key, Player* player) { return PlaceholderAPI::getValue(key, player); }

bool registerPlayerPlaceholder(
    std::string const& PluginName,
    std::string const& FuncName,
    std::string const& PAPIName
) {
    if (RemoteCall::hasFunc(PluginName, FuncName)) {
        PlaceholderAPI::unregisterPlaceholder(PAPIName);
        if (isParameters(PAPIName)) {
            auto Call = RemoteCall::importAs<std::string(Player * pl, std::unordered_map<std::string, std::string>)>(
                PluginName,
                FuncName
            );
            PlaceholderAPI::registerPlayerPlaceholder(
                PAPIName,
                [Call](Player* sp, std::unordered_map<std::string, std::string> map) { return Call(sp, map); },
                PluginName
            );
        } else {
            auto Call = RemoteCall::importAs<std::string(Player * pl)>(PluginName, FuncName);
            PlaceholderAPI::registerPlayerPlaceholder(
                PAPIName,
                [Call](Player* sp) { return Call(sp); },
                PluginName
            );
        }
        return true;
    }
    return false;
}

bool registerServerPlaceholder(
    std::string const& PluginName,
    std::string const& FuncName,
    std::string const& PAPIName
) {
    if (RemoteCall::hasFunc(PluginName, FuncName)) {
        PlaceholderAPI::unregisterPlaceholder(PAPIName);
        if (isParameters(PAPIName)) {
            auto Call =
                RemoteCall::importAs<std::string(std::unordered_map<std::string, std::string>)>(PluginName, FuncName);
            PlaceholderAPI::registerServerPlaceholder(
                PAPIName,
                [Call](std::unordered_map<std::string, std::string> map) { return Call(map); },
                PluginName
            );
        } else {
            auto Call = RemoteCall::importAs<std::string()>(PluginName, FuncName);
            PlaceholderAPI::registerServerPlaceholder(PAPIName, [Call]() { return Call(); }, PluginName);
        }
        return true;
    }
    return false;
}

bool registerStaticPlaceholder(
    std::string const& PluginName,
    std::string const& FuncName,
    std::string const& PAPIName,
    int                num
) {
    if (RemoteCall::hasFunc(PluginName, FuncName)) {
        PlaceholderAPI::unregisterPlaceholder(PAPIName);
        if (isParameters(PAPIName)) {
            auto Call = RemoteCall::importAs<std::string()>(PluginName, FuncName);
            if (num == -1) {
                PlaceholderAPI::registerStaticPlaceholder(
                    PAPIName,
                    [Call] { return Call(); },
                    PluginName
                );
            } else {
                PlaceholderAPI::registerStaticPlaceholder(
                    PAPIName,
                    num,
                    [Call] { return Call(); },
                    PluginName
                );
            }
        }
        return true;
    }
    return false;
}

std::string translateStringWithPlayer(std::string const& str, Player* pl) {
    return PlaceholderAPI::translateString(str, pl);
}

std::string translateString(std::string const& str) { return PlaceholderAPI::translateString(str); }

bool unRegisterPlaceholder(std::string const& str) { return PlaceholderAPI::unregisterPlaceholder(str); }

std::vector<std::string> getAllPAPI() { return PlaceholderAPI::getAllPAPI(); }

} // namespace PAPIRemoteCall

#define EXPORTAPI(T)                                                                                                   \
    RemoteCall::exportAs("BEPlaceholderAPI", ll::utils::string_utils::replaceAll(#T, "PAPIRemoteCall::", ""), T);

void ExportPAPI() {
    EXPORTAPI(PAPIRemoteCall::registerPlayerPlaceholder);
    EXPORTAPI(PAPIRemoteCall::registerServerPlaceholder);
    EXPORTAPI(PAPIRemoteCall::registerStaticPlaceholder);
    EXPORTAPI(PAPIRemoteCall::GetValue);
    EXPORTAPI(PAPIRemoteCall::GetValueWithPlayer);
    EXPORTAPI(PAPIRemoteCall::translateString);
    EXPORTAPI(PAPIRemoteCall::translateStringWithPlayer);
    EXPORTAPI(PAPIRemoteCall::unRegisterPlaceholder);
    EXPORTAPI(PAPIRemoteCall::getAllPAPI);
}