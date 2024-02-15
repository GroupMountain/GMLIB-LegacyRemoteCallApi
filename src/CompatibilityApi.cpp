#include "Global.h"

void Export_Compatibility_API() {
    RemoteCall::exportAs("GMLIB_API", "getServerMspt", []() -> float {
        auto level = GMLIB_Level::getLevel();
        if (!level) {
            return 0.0f;
        }
        return level->getServerMspt();
    });
    RemoteCall::exportAs("GMLIB_API", "getServerCurrentTps", []() -> float {
        auto level = GMLIB_Level::getLevel();
        if (!level) {
            return 0.0f;
        }
        return level->getServerCurrentTps();
    });
    RemoteCall::exportAs("GMLIB_API", "getServerAverageTps", []() -> float {
        auto level = GMLIB_Level::getLevel();
        if (!level) {
            return 0.0f;
        }
        return level->getServerAverageTps();
    });
    RemoteCall::exportAs("GMLIB_API", "getAllPlayerUuids", []() -> std::vector<std::string> {
        return GMLIB_Player::getAllUuids();
    });
    RemoteCall::exportAs("GMLIB_API", "getAllExperiments", []() -> std::vector<int> {
        return {6, 7, 8, 9, 10, 13, 16, 17, 18};
    });
    RemoteCall::exportAs("GMLIB_API", "getExperimentTranslatedName", [](int id) -> std::string {
        auto map = GMLIB_Level::getAllExperimentsTranslateKeys();
        if (map.count(id)) {
            return map[id];
        }
        return "";
    });
}