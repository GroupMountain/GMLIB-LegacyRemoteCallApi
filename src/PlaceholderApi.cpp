#include "Global.h"
#include <regex>

namespace PAPIRemoteCall {
std::string GetValue(std::string const& from) { return PlaceholderAPI::getValue(from, std::nullopt).value_or(""); }

std::string GetValueWithPlayer(std::string const& key, Player* player) {
    return PlaceholderAPI::getValue(key, (GMActor*)player).value_or("");
}

void registerPlayerPlaceholder(
    std::string const& PluginName,
    std::string const& FuncName,
    std::string const& PAPIName
) {
    if (!RemoteCall::hasFunc(PluginName, FuncName)) return;
    auto func = [=]() -> void {
        PlaceholderAPI::unregisterPlaceholder(PAPIName);
        std::weak_ptr mod = ll::mod::ModManagerRegistry::getInstance().getMod(PluginName);
        if (mod.expired()) return;
        PlaceholderAPI::registerPlaceholder(
            PAPIName,
            [Call = RemoteCall::importAs<std::string(Player * pl, std::unordered_map<std::string, std::string>)>(
                 PluginName,
                 FuncName
             )](optional_ref<Actor> actor, ll::StringMap<std::string> const& params, auto&&...
            ) -> std::optional<std::string> {
                if (actor.has_value() && ((Actor*)actor.as_ptr())->isPlayer()) {
                    std::unordered_map<std::string, std::string> paramMap;
                    for (auto& [key, val] : params) {
                        paramMap[key] = val;
                    }
                    return Call((Player*)actor.as_ptr(), paramMap);
                }
                return std::nullopt;
            },
            mod
        );
    };
    if (ll::mod::ModManagerRegistry::getInstance().hasMod(PluginName)) {
        func();
    } else {
        getThreadPoolExecutor().execute(func);
    }
}

void registerServerPlaceholder(
    std::string const& PluginName,
    std::string const& FuncName,
    std::string const& PAPIName
) {
    if (!RemoteCall::hasFunc(PluginName, FuncName)) return;
    auto func = [=]() -> void {
        PlaceholderAPI::unregisterPlaceholder(PAPIName);
        std::weak_ptr mod = ll::mod::ModManagerRegistry::getInstance().getMod(PluginName);
        if (mod.expired()) return;
        PlaceholderAPI::registerPlaceholder(
            PAPIName,
            [Call = RemoteCall::importAs<std::string(std::unordered_map<std::string, std::string>)>(
                 PluginName,
                 FuncName
             )](auto, ll::StringMap<std::string> const& params, auto&&...) -> std::optional<std::string> {
                std::unordered_map<std::string, std::string> paramMap;
                for (auto& [key, val] : params) {
                    paramMap[key] = val;
                }
                return Call(paramMap);
            },
            mod
        );
    };
    if (ll::mod::ModManagerRegistry::getInstance().hasMod(PluginName)) {
        func();
    } else {
        getThreadPoolExecutor().execute(func);
    }
}

void registerStaticPlaceholder(
    std::string const& PluginName,
    std::string const& FuncName,
    std::string const& PAPIName,
    int                num
) {
    if (!RemoteCall::hasFunc(PluginName, FuncName)) return;
    auto func = [=]() -> void {
        PlaceholderAPI::unregisterPlaceholder(PAPIName);
        std::weak_ptr mod = ll::mod::ModManagerRegistry::getInstance().getMod(PluginName);
        if (mod.expired()) return;
        PlaceholderAPI::registerPlaceholder(
            PAPIName,
            [Call = RemoteCall::importAs<std::string()>(PluginName, FuncName)](auto&&...)
                -> std::optional<std::string> { return Call(); },
            mod
        );
    };
    if (ll::mod::ModManagerRegistry::getInstance().hasMod(PluginName)) {
        func();
    } else {
        getThreadPoolExecutor().execute(func);
    }
}

std::string translateStringWithPlayer(std::string const& str, Player* pl) {
    return PlaceholderAPI::translate(str, (GMActor*)pl);
}

std::string translateString(std::string const& str) { return PlaceholderAPI::translate(str, std::nullopt); }

bool unRegisterPlaceholder(std::string const& str) { return PlaceholderAPI::unregisterPlaceholder(str); }

std::vector<std::string> getAllPAPI() {
    std::vector<std::string> result;
    for (auto& papi : PlaceholderAPI::getAllPlaceholderData()) {
        result.push_back(papi.first);
    }
    return result;
}

} // namespace PAPIRemoteCall

namespace NewPapiRemoteCall {
std::string translate(std::string const& value, std::string const& language) {
    return PlaceholderAPI::translate(value, std::nullopt, language);
}
std::string translateFromActor(std::string const& value, Actor* actor, std::string const& language) {
    return PlaceholderAPI::translate(value, (GMActor*)actor, language);
}
void registerPlaceholder(std::string const& placeholder, std::string const& funcName, std::string const& pluginName) {
    if (!RemoteCall::hasFunc(pluginName, funcName)) return;
    auto func = [=]() -> void {
        if (std::weak_ptr mod = ll::mod::ModManagerRegistry::getInstance().getMod(pluginName); !mod.expired()) {
            PlaceholderAPI::unregisterPlaceholder(placeholder);
            PlaceholderAPI::registerPlaceholder(
                placeholder,
                [Call = RemoteCall::importAs<
                     std::string(Actor*, std::unordered_map<std::string, std::string>, std::string)>(
                     pluginName,
                     funcName
                 )](optional_ref<Actor> actor, ll::StringMap<std::string> const& params, std::string const& language
                ) -> std::optional<std::string> {
                    std::unordered_map<std::string, std::string> paramMap;
                    for (auto& [key, val] : params) {
                        paramMap[key] = val;
                    }
                    auto result = Call((Actor*)actor.as_ptr(), paramMap, language);
                    return result == "<std::nullopt>" ? std::nullopt : std::optional(result);
                },
                mod
            );
        }
    };
    if (ll::mod::ModManagerRegistry::getInstance().hasMod(pluginName)) {
        func();
    } else {
        getThreadPoolExecutor().execute(func);
    }
}
bool unregisterPlaceholder(std::string const& placeholder) {
    return PlaceholderAPI::unregisterPlaceholder(placeholder);
}
bool unregisterPlaceholderFromModName(std::string const& pluginName) {
    std::weak_ptr plugin = ll::mod::ModManagerRegistry::getInstance().getMod(pluginName);
    if (plugin.expired()) return false;
    return PlaceholderAPI::unregisterPlaceholder(plugin);
}
std::string getValue(
    std::string const&                           placeholder,
    std::unordered_map<std::string, std::string> params,
    std::string const&                           language
) {
    ll::StringMap<std::string> paramMap;
    for (auto& [key, val] : params) {
        paramMap[key] = val;
    }
    return PlaceholderAPI::getValue(placeholder, std::nullopt, paramMap, language).value_or("<std::nullopt>");
}
std::string getValueFromActor(
    std::string const&                           placeholder,
    Actor*                                       actor,
    std::unordered_map<std::string, std::string> params,
    std::string const&                           language
) {
    ll::StringMap<std::string> paramMap;
    for (auto& [key, val] : params) {
        paramMap[key] = val;
    }
    return PlaceholderAPI::getValue(placeholder, (GMActor*)actor, paramMap, language).value_or("<std::nullopt>");
}
} // namespace NewPapiRemoteCall

#define EXPORTAPI(T)                                                                                                   \
    RemoteCall::exportAs("BEPlaceholderAPI", ll::utils::string_utils::replaceAll(#T, "PAPIRemoteCall::", ""), T);

#define EXPORTAPI2(T) RemoteCall::exportAs("PlaceholderAPI", #T, NewPapiRemoteCall::T);

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

    EXPORTAPI2(translate);
    EXPORTAPI2(translateFromActor);
    EXPORTAPI2(registerPlaceholder);
    EXPORTAPI2(unregisterPlaceholder);
    EXPORTAPI2(unregisterPlaceholderFromModName);
    EXPORTAPI2(getValue);
    EXPORTAPI2(getValueFromActor);
}