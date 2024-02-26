#pragma once

#include <ll/api/plugin/NativePlugin.h>

namespace GMLIB_LegacyRemoteCallApi {

[[nodiscard]] auto getSelfPluginInstance() -> ll::plugin::NativePlugin&;

} // namespace GMLIB_LegacyRemoteCallApi
