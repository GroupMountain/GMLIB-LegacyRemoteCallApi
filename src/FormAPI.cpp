#include "Global.h"

using namespace GMLIB::Server::Form;
using namespace ll::hash_utils;

class LegacyScriptFormManager {
private:
    int64 mNextFormCallbackId = 0;
    // std::unordered_map<int64, ll::event::ListenerPtr> mEventListeners;

public:
    std::string getNextFormCallbackId() {
        mNextFormCallbackId++;
        return "GMLIB_EVENT_" + std::to_string(mNextFormCallbackId);
    }

public:
    static LegacyScriptFormManager& getInstance() {
        static std::unique_ptr<LegacyScriptFormManager> instance;
        if (!instance) {
            instance = std::make_unique<LegacyScriptFormManager>();
        }
        return *instance;
    }
};

#define PLAYER_DETECROR                                                                                                \
    [detectorId, result](Player& pl) -> bool {                                                                         \
        try {                                                                                                          \
            if (RemoteCall::hasFunc("GMLIB_FORM_CALLBACK", detectorId)) {                                              \
                auto const& detector = RemoteCall::importAs<bool(Player*)>("GMLIB_FORM_CALLBACK", detectorId);         \
                return detector(&pl);                                                                                  \
            } else {                                                                                                   \
                ServerSettingForm::removeElement(result);                                                              \
            }                                                                                                          \
        } catch (...) {}                                                                                               \
        return false;                                                                                                  \
    }

#define CALLBACK_TYPE_STRING                                                                                           \
    [callbackId, result](Player& pl, std::string const& data) {                                                        \
        try {                                                                                                          \
            if (RemoteCall::hasFunc("GMLIB_FORM_CALLBACK", callbackId)) {                                              \
                auto const& callback =                                                                                 \
                    RemoteCall::importAs<void(Player*, std::string const&)>("GMLIB_FORM_CALLBACK", callbackId);        \
                callback(&pl, data);                                                                                   \
            } else {                                                                                                   \
                ServerSettingForm::removeElement(result);                                                              \
            }                                                                                                          \
        } catch (...) {}                                                                                               \
    }

#define CALLBACK_TYPE_BOOL                                                                                             \
    [callbackId, result](Player& pl, bool data) {                                                                      \
        try {                                                                                                          \
            if (RemoteCall::hasFunc("GMLIB_FORM_CALLBACK", callbackId)) {                                              \
                auto const& callback = RemoteCall::importAs<void(Player*, bool)>("GMLIB_FORM_CALLBACK", callbackId);   \
                callback(&pl, data);                                                                                   \
            } else {                                                                                                   \
                ServerSettingForm::removeElement(result);                                                              \
            }                                                                                                          \
        } catch (...) {}                                                                                               \
    }

#define CALLBACK_TYPE_DOUBLE                                                                                           \
    [callbackId, result](Player& pl, double data) {                                                                    \
        try {                                                                                                          \
            if (RemoteCall::hasFunc("GMLIB_FORM_CALLBACK", callbackId)) {                                              \
                auto const& callback = RemoteCall::importAs<void(Player*, double)>("GMLIB_FORM_CALLBACK", callbackId); \
                callback(&pl, data);                                                                                   \
            } else {                                                                                                   \
                ServerSettingForm::removeElement(result);                                                              \
            }                                                                                                          \
        } catch (...) {}                                                                                               \
    }


#define CALLBACK_TYPE_LONG                                                                                             \
    [callbackId, result](Player& pl, int64 data) {                                                                     \
        try {                                                                                                          \
            if (RemoteCall::hasFunc("GMLIB_FORM_CALLBACK", callbackId)) {                                              \
                auto const& callback = RemoteCall::importAs<void(Player*, int64)>("GMLIB_FORM_CALLBACK", callbackId);  \
                callback(&pl, data);                                                                                   \
            } else {                                                                                                   \
                ServerSettingForm::removeElement(result);                                                              \
            }                                                                                                          \
        } catch (...) {}                                                                                               \
    }


void Export_Form_API() {
    RemoteCall::exportAs("GMLIB_ServerSettingForm", "getDefaultPriority", []() -> int {
        return ServerSettingForm::getDefaultPriority();
    });
    RemoteCall::exportAs("GMLIB_FormAPI", "getNextFormCallbackId", []() -> std::string {
        return LegacyScriptFormManager::getInstance().getNextFormCallbackId();
    });
    RemoteCall::exportAs("GMLIB_ServerSettingForm", "hasTitle", []() -> bool { return ServerSettingForm::hasTitle(); });
    RemoteCall::exportAs("GMLIB_ServerSettingForm", "getTitle", []() -> std::string {
        return ServerSettingForm::getTitle();
    });
    RemoteCall::exportAs("GMLIB_ServerSettingForm", "setTitle", [](std::string const& title, bool forceModify) -> bool {
        return ServerSettingForm::setTitle(title, forceModify);
    });
    RemoteCall::exportAs("GMLIB_ServerSettingForm", "hasIcon", []() -> bool { return ServerSettingForm::hasIcon(); });
    RemoteCall::exportAs("GMLIB_ServerSettingForm", "getIconData", []() -> std::string {
        if (auto data = ServerSettingForm::getIconData()) {
            return data.value();
        }
        return "";
    });
    RemoteCall::exportAs("GMLIB_ServerSettingForm", "getIconType", []() -> int {
        if (auto type = ServerSettingForm::getIconType()) {
            return (int)type.value();
        }
        return -1;
    });
    RemoteCall::exportAs(
        "GMLIB_ServerSettingForm",
        "setIcon",
        [](std::string const& title, uchar type, bool forceModify) -> bool {
            return ServerSettingForm::setIcon(title, IconType(type), forceModify);
        }
    );
    RemoteCall::exportAs(
        "GMLIB_ServerSettingForm",
        "addLabel",
        [](std::string const& text, std::string const& detectorId, int priority) -> uint {
            uint result = ServerSettingForm::addLabel(text, PLAYER_DETECROR, priority);
            return result;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_ServerSettingForm",
        "addInput",
        [](std::string const& text,
           std::string const& placeholder,
           std::string const& defaultVal,
           std::string const& callbackId,
           std::string const& detectorId,
           int                priority) -> uint {
            uint result = ServerSettingForm::addInput(
                text,
                placeholder,
                defaultVal,
                CALLBACK_TYPE_STRING,
                PLAYER_DETECROR,
                priority
            );
            return result;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_ServerSettingForm",
        "addToggle",
        [](std::string const& text,
           bool               defaultVal,
           std::string const& callbackId,
           std::string const& detectorId,
           int                priority) -> uint {
            uint result = ServerSettingForm::addToggle(text, defaultVal, CALLBACK_TYPE_BOOL, PLAYER_DETECROR, priority);
            return result;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_ServerSettingForm",
        "addDropdown",
        [](std::string const&       text,
           std::vector<std::string> options,
           int64                    defaultVal,
           std::string const&       callbackId,
           std::string const&       detectorId,
           int                      priority) -> uint {
            uint result = ServerSettingForm::addDropdown(
                text,
                options,
                defaultVal,
                CALLBACK_TYPE_LONG,
                PLAYER_DETECROR,
                priority
            );
            return result;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_ServerSettingForm",
        "addSlider",
        [](std::string const& text,
           double             min,
           double             max,
           double             step,
           double             defaultVal,
           std::string const& callbackId,
           std::string const& detectorId,
           int                priority) -> uint {
            uint result = ServerSettingForm::addSlider(
                text,
                min,
                max,
                step,
                defaultVal,
                CALLBACK_TYPE_DOUBLE,
                PLAYER_DETECROR,
                priority
            );
            return result;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_ServerSettingForm",
        "addStepSlider",
        [](std::string const&       text,
           std::vector<std::string> steps,
           int64                    defaultVal,
           std::string const&       callbackId,
           std::string const&       detectorId,
           int                      priority) -> uint {
            uint result = ServerSettingForm::addStepSlider(
                text,
                steps,
                defaultVal,
                CALLBACK_TYPE_LONG,
                PLAYER_DETECROR,
                priority
            );
            return result;
        }
    );
    RemoteCall::exportAs("GMLIB_ServerSettingForm", "removeElement", [](uint id) -> bool {
        return ServerSettingForm::removeElement(id);
    });
}