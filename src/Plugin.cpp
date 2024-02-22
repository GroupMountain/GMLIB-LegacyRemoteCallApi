#include "Plugin.h"
#include "Global.h"

ll::Logger logger(PLUGIN_NAME);

namespace plugin {

Plugin::Plugin(ll::plugin::NativePlugin& self) : mSelf(self) {
    // Code for loading the plugin goes here.
    Export_Legacy_GMLib_ModAPI();
    Export_Legacy_GMLib_ServerAPI();
    Export_Compatibility_API();
    ExportPAPI();
    logger.info("GMLIB-LegacyRemoteCallApi Loaded!");
    logger.info("Author: GroupMountain");
    logger.info("Repository: https://github.com/GroupMountain/GMLIB-LegacyRemoteCallApi");
}

bool Plugin::enable() {
    // Code for enabling the plugin goes here.
    return true;
}

bool Plugin::disable() {
    // Code for disabling the plugin goes here.
    return true;
}

} // namespace plugin