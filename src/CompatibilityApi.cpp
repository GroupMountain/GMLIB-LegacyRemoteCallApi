#include "Global.h"

void Export_Compatibility_API() {
    RemoteCall::exportAs("GMLIB_API", "getServerMspt", []() -> float {
        return GMLIB_Level::getLevel()->getServerMspt();
    });
    RemoteCall::exportAs("GMLIB_API", "getServerCurrentTps", []() -> float {
        return GMLIB_Level::getLevel()->getServerCurrentTps();
    });
    RemoteCall::exportAs("GMLIB_API", "getServerAverageTps", []() -> float {
        return GMLIB_Level::getLevel()->getServerAverageTps();
    });
    RemoteCall::exportAs("GMLIB_API", "getAllPlayerUuids", []() -> std::vector<std::string> {
        return GMLIB_Player::getAllUuids();
    });
}