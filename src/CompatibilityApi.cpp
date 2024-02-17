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
        auto             map = GMLIB_Level::getAllExperiments();
        std::vector<int> result;
        for (auto& key : map) {
            result.push_back(key.first);
        }
        return result;
    });
    RemoteCall::exportAs("GMLIB_API", "getExperimentTranslatedName", [](int id) -> std::string {
        auto map = GMLIB_Level::getAllExperimentsTranslateKeys();
        if (map.count(id)) {
            return map[id];
        }
        return "";
    });
    RemoteCall::exportAs("GMLIB_API", "createFloatingText", [](std::pair<Vec3, int> pos, std::string text) -> int {
        auto ft = new GMLIB::Server::FloatingText(text, pos.first, pos.second);
        return ft->getRuntimeID();
    });
    RemoteCall::exportAs("GMLIB_API", "setFloatingTextData", [](int id, std::string text) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->setText(text);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "deleteFloatingText", [](int id) -> bool {
        return GMLIB::Server::FloatingText::deleteFloatingText(id);
    });
    RemoteCall::exportAs("GMLIB_API", "sendFloatingTextToPlayer", [](int id, Player* pl) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->sendToClient(pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "sendFloatingText", [](int id) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->sendToAllClients();
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "removeFloatingTextFromPlayer", [](int id, Player* pl) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->removeFromClient(pl);
            return true;
        }
        return false;
    });
    RemoteCall::exportAs("GMLIB_API", "removeFloatingText", [](int id) -> bool {
        auto ft = GMLIB::Server::FloatingText::getFloatingText(id);
        if (ft) {
            ft->removeFromAllClients();
            return true;
        }
        return false;
    });
}