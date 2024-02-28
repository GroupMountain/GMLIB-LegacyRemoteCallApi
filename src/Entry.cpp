#include "Entry.h"
#include "Global.h"

ll::Logger logger(PLUGIN_NAME);

namespace GMLIB_LegacyRemoteCallApi {

namespace {

std::unique_ptr<std::reference_wrapper<ll::plugin::NativePlugin>>
    selfPluginInstance; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

auto disable(ll::plugin::NativePlugin& /*self*/) -> bool { return false; }

auto enable(ll::plugin::NativePlugin& /*self*/) -> bool { return true; }

auto load(ll::plugin::NativePlugin& self) -> bool {
    selfPluginInstance = std::make_unique<std::reference_wrapper<ll::plugin::NativePlugin>>(self);
    Export_Legacy_GMLib_ModAPI();
    Export_Legacy_GMLib_ServerAPI();
    Export_GMLib_FakeListAPI();
    Export_Compatibility_API();
    ExportPAPI();
    logger.info("GMLIB-LegacyRemoteCallApi Loaded!");
    logger.info("Version: {}", LIB_VERSION.asString());
    logger.info("Author: GroupMountain");
    logger.info("Repository: https://github.com/GroupMountain/GMLIB-LegacyRemoteCallApi");
    return true;
}

auto unload(ll::plugin::NativePlugin& self) -> bool { return false; }

} // namespace

auto getSelfPluginInstance() -> ll::plugin::NativePlugin& {
    if (!selfPluginInstance) {
        throw std::runtime_error("selfPluginInstance is null");
    }

    return *selfPluginInstance;
}

} // namespace GMLIB_LegacyRemoteCallApi

extern "C" {
_declspec(dllexport) auto ll_plugin_disable(ll::plugin::NativePlugin& self) -> bool {
    return GMLIB_LegacyRemoteCallApi::disable(self);
}
_declspec(dllexport) auto ll_plugin_enable(ll::plugin::NativePlugin& self) -> bool {
    return GMLIB_LegacyRemoteCallApi::enable(self);
}
_declspec(dllexport) auto ll_plugin_load(ll::plugin::NativePlugin& self) -> bool {
    return GMLIB_LegacyRemoteCallApi::load(self);
}
_declspec(dllexport) auto ll_plugin_unload(ll::plugin::NativePlugin& self) -> bool {
    return GMLIB_LegacyRemoteCallApi::unload(self);
}
}
