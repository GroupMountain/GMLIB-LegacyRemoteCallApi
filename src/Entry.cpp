#include "Entry.h"
#include "Global.h"

namespace gmlib {

LegacyRemoteCallApi& LegacyRemoteCallApi::getInstance() {
    static LegacyRemoteCallApi instance;
    return instance;
}

bool LegacyRemoteCallApi::load() {
    Export_Legacy_GMLib_ModAPI();
    Export_Legacy_GMLib_ServerAPI();
    Export_Compatibility_API();
    ExportPAPI();
    // Export_Event_API();
    Export_BinaryStream_API();
    // Export_Form_API();
    auto logger = ll::io::LoggerRegistry::getInstance().getOrCreate(PLUGIN_NAME);
    logger->info("GMLIB-LegacyRemoteCallApi Loaded!");
    logger->info(
        "Loaded Version: {} with {}",
        fmt::format(fg(fmt::color::pink), "GMLIB-" GMLIB_FILE_VERSION_STRING),
        fmt::format(fg(fmt::color::light_green), "GMLIB-LegacyRemoteCallApi-" + LIB_VERSION.to_string())
    );
    logger->info("Author: GroupMountain");
    logger->info("Repository: https://github.com/GroupMountain/GMLIB-LegacyRemoteCallApi");
    return true;
}

bool LegacyRemoteCallApi::enable() { return true; }

bool LegacyRemoteCallApi::disable() { return true; }

} // namespace gmlib

LL_REGISTER_MOD(gmlib::LegacyRemoteCallApi, gmlib::LegacyRemoteCallApi::getInstance());


ll::thread::ThreadPoolExecutor const& getThreadPoolExecutor() {
    return gmlib::LegacyRemoteCallApi::getInstance().getThreadPoolExecutor();
}