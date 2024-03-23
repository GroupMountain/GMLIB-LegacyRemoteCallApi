#include "Entry.h"
#include "Global.h"

ll::Logger logger(PLUGIN_NAME);

namespace GMLIB_LegacyRemoteCallApi {

std::unique_ptr<LRCA>& LRCA::getInstance() {
    static std::unique_ptr<LRCA> instance;
    return instance;
}

bool LRCA::load() {
    Export_Legacy_GMLib_ModAPI();
    Export_Legacy_GMLib_ServerAPI();
    Export_Compatibility_API();
    ExportPAPI();
    Export_Event_API();
    logger.info("GMLIB-LegacyRemoteCallApi Loaded!");
    logger.info("Version: {}", LIB_VERSION.asString());
    logger.info("Author: GroupMountain");
    logger.info("Repository: https://github.com/GroupMountain/GMLIB-LegacyRemoteCallApi");
    return true;
}

bool LRCA::enable() { return true; }

bool LRCA::disable() { return true; }

} // namespace GMLIB_LegacyRemoteCallApi

LL_REGISTER_PLUGIN(GMLIB_LegacyRemoteCallApi::LRCA, GMLIB_LegacyRemoteCallApi::LRCA::getInstance());
