#include "Global.h"
#include <regex>

namespace PAPIRemoteCall {

std::string removeBrackets(std::string a1) {
    a1.erase(a1.find_last_not_of("%") + 1);
    return a1;
}

bool isParameters(std::string str) {
    std::regex reg("[<]([^<>]+)[>]");
    return std::regex_search(removeBrackets(str), reg);
}

std::string GetValue(std::string const& from) { return GMLIB::Server::PlaceholderAPI::getValue(from); }

std::string GetValueWithPlayer(std::string const& a1, std::string const& a2) {
    return GMLIB::Server::PlaceholderAPI::getValue(a1, ll::service::bedrock::getLevel()->getPlayer(a2));
}

std::string
registerPlayerPlaceholder(std::string const& PluginName, std::string const& FuncName, std::string const& PAPIName) {
    if (RemoteCall::hasFunc(PluginName, FuncName)) {
        if (isParameters(PAPIName)) {
            auto Call =
                RemoteCall::importAs<std::string(std::string const& arg, std::unordered_map<std::string, std::string>)>(
                    PluginName,
                    FuncName
                );
            GMLIB::Server::PlaceholderAPI::registerPlayerPlaceholder(
                PAPIName,
                [Call](Player* sp, std::unordered_map<std::string, std::string> map) {
                    return Call(sp->getXuid(), map);
                },
                PluginName
            );
        } else {
            auto Call = RemoteCall::importAs<std::string(std::string const& arg)>(PluginName, FuncName);
            GMLIB::Server::PlaceholderAPI::registerPlayerPlaceholder(
                PAPIName,
                [Call](Player* sp) { return Call(sp->getXuid()); },
                PluginName
            );
        }
    } else {
        // logger.error("Function no find({}:{})", PluginName, FuncName);
        return "Function no find";
    }
    return "Register Success";
}

std::string
registerServerPlaceholder(std::string const& PluginName, std::string const& FuncName, std::string const& PAPIName) {
    if (RemoteCall::hasFunc(PluginName, FuncName)) {
        if (isParameters(PAPIName)) {
            auto Call =
                RemoteCall::importAs<std::string(std::unordered_map<std::string, std::string>)>(PluginName, FuncName);
            GMLIB::Server::PlaceholderAPI::registerServerPlaceholder(
                PAPIName,
                [Call](std::unordered_map<std::string, std::string> map) { return Call(map); },
                PluginName
            );
        } else {
            auto Call = RemoteCall::importAs<std::string()>(PluginName, FuncName);
            GMLIB::Server::PlaceholderAPI::registerServerPlaceholder(
                PAPIName,
                [Call]() { return Call(); },
                PluginName
            );
        }
    } else {
        // logger.error("Function no find({}:{})", PluginName, FuncName);
        return "Function no find";
    }
    return "Register Success";
}

std::string registerStaticPlaceholder(
    std::string const& PluginName,
    std::string const& FuncName,
    std::string const& PAPIName,
    int                num
) {
    if (RemoteCall::hasFunc(PluginName, FuncName)) {
        if (isParameters(PAPIName)) {
            auto Call = RemoteCall::importAs<std::string()>(PluginName, FuncName);
            if (num == -1) {
                GMLIB::Server::PlaceholderAPI::registerStaticPlaceholder(
                    PAPIName,
                    [Call] { return Call(); },
                    PluginName
                );
            } else {
                GMLIB::Server::PlaceholderAPI::registerStaticPlaceholder(
                    PAPIName,
                    num,
                    [Call] { return Call(); },
                    PluginName
                );
            }
        }
    } else {
        // logger.error("Function no find({}:{})", PluginName, FuncName);
        return "Function no find";
    }
    return "Register Success";
}

std::string translateString(std::string const& str, std::string const& xuid) {
    return GMLIB::Server::PlaceholderAPI::translateString(str, ll::service::bedrock::getLevel()->getPlayerByXuid(xuid));
}

bool unRegisterPlaceholder(std::string const& str) { return GMLIB::Server::PlaceholderAPI::unRegisterPlaceholder(str); }

std::vector<std::string> getAllPAPI() { return GMLIB::Server::PlaceholderAPI::getAllPAPI(); }

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
    EXPORTAPI(PAPIRemoteCall::unRegisterPlaceholder);
    EXPORTAPI(PAPIRemoteCall::getAllPAPI);
}