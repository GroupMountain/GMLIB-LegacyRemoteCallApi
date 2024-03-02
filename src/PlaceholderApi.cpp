#include "Global.h"
#include <regex>

namespace PAPIRemoteCall {

std::string GetValue(std::string const& from) { return GMLIB::Server::PlaceholderAPI::getValue(from); }

std::string GetValueWithPlayer(std::string const& a1, std::string const& a2) {
    return GMLIB::Server::PlaceholderAPI::getValue(a1, ll::service::bedrock::getLevel()->getPlayer(a2));
}

bool registerPlayerPlaceholder(
    std::string const& PluginName,
    std::string const& FuncName,
    std::string const& PAPIName
) {
    if (RemoteCall::hasFunc(PluginName, FuncName)) {
        auto Call = RemoteCall::importAs<std::string(Player * pl)>(PluginName, FuncName);
        GMLIB::Server::PlaceholderAPI::registerPlayerPlaceholder(
            PAPIName,
            [Call](Player* sp) { return Call(sp); },
            PluginName
        );
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
        auto Call = RemoteCall::importAs<std::string()>(PluginName, FuncName);
        GMLIB::Server::PlaceholderAPI::registerServerPlaceholder(
            PAPIName,
            [Call]() { return Call(); },
            PluginName
        );
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
        return true;
    }
    return false;
}

std::string translateStringWithPlayer(std::string const& str, Player* pl) {
    return GMLIB::Server::PlaceholderAPI::translateString(str, pl);
}

std::string translateString(std::string const& str) { return GMLIB::Server::PlaceholderAPI::translateString(str); }

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
    EXPORTAPI(PAPIRemoteCall::translateStringWithPlayer);
    EXPORTAPI(PAPIRemoteCall::unRegisterPlaceholder);
    EXPORTAPI(PAPIRemoteCall::getAllPAPI);
}