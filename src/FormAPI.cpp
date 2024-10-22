#include "Global.h"

using namespace ll::hash_utils;

// class LegacyScriptFormManager {
// private:
//     int64 mNextFormCallbackId = 0;

// public:
//     std::string getNextFormCallbackId() {
//         return "GMLIB_FormApi_" + std::to_string(mNextFormCallbackId++);
//     }

// public:
//     static LegacyScriptFormManager& getInstance() {
//         static std::unique_ptr<LegacyScriptFormManager> instance;
//         if (!instance) instance = std::make_unique<LegacyScriptFormManager>();
//         return *instance;
//     }
// };

#define PLAYER_DETECROR                                                                                                \
    [detectorId, result](Player& pl) -> bool {                                                                         \
        try {                                                                                                          \
            if (RemoteCall::hasFunc("GMLIB_FORM_CALLBACK", detectorId)) {                                              \
                auto const& detector = RemoteCall::importAs<bool(Player*)>("GMLIB_FORM_CALLBACK", detectorId);         \
                return detector(&pl);                                                                                  \
            } else {                                                                                                   \
                gmlib::form::ServerSettingForm::removeElement(result);                                                 \
            }                                                                                                          \
        } catch (...) {}                                                                                               \
        return false;                                                                                                  \
    }

#define CALLBACK_TYPE(type)                                                                                            \
    [callbackId, result](Player& pl, type data) {                                                                      \
        try {                                                                                                          \
            if (RemoteCall::hasFunc("GMLIB_FORM_CALLBACK", callbackId)) {                                              \
                auto const& callback = RemoteCall::importAs<void(Player*, type)>("GMLIB_FORM_CALLBACK", callbackId);   \
                callback(&pl, data);                                                                                   \
            } else {                                                                                                   \
                gmlib::form::ServerSettingForm::removeElement(result);                                                 \
            }                                                                                                          \
        } catch (...) {}                                                                                               \
    }

void Export_Form_API() {
    RemoteCall::exportAs("GMLIB_gmlib::form::ServerSettingForm", "getDefaultPriority", []() -> int {
        return gmlib::form::ServerSettingForm::getDefaultPriority();
    });
    // RemoteCall::exportAs("GMLIB_FormAPI", "getNextFormCallbackId", []() -> std::string {
    //     return LegacyScriptFormManager::getInstance().getNextFormCallbackId();
    // });
    RemoteCall::exportAs("GMLIB_gmlib::form::ServerSettingForm", "hasTitle", []() -> bool { return gmlib::form::ServerSettingForm::hasTitle(); });
    RemoteCall::exportAs("GMLIB_gmlib::form::ServerSettingForm", "getTitle", []() -> std::string {
        return gmlib::form::ServerSettingForm::getTitle();
    });
    RemoteCall::exportAs("GMLIB_gmlib::form::ServerSettingForm", "setTitle", [](std::string const& title, bool forceModify) -> bool {
        return gmlib::form::ServerSettingForm::setTitle(title, forceModify);
    });
    RemoteCall::exportAs("GMLIB_gmlib::form::ServerSettingForm", "hasIcon", []() -> bool { return gmlib::form::ServerSettingForm::hasIcon(); });
    RemoteCall::exportAs("GMLIB_gmlib::form::ServerSettingForm", "getIconData", []() -> std::string {
        return gmlib::form::ServerSettingForm::getIconData().value_or("");
    });
    RemoteCall::exportAs("GMLIB_gmlib::form::ServerSettingForm", "getIconType", []() -> int {
        return gmlib::form::ServerSettingForm::getIconType()
            .transform([](gmlib::form::IconType&& type) -> int { return (int)type; })
            .value_or(-1);
    });
    RemoteCall::exportAs(
        "GMLIB_gmlib::form::ServerSettingForm",
        "setIcon",
        [](std::string const& title, uchar type, bool forceModify) -> bool {
            return gmlib::form::ServerSettingForm::setIcon(title, gmlib::form::IconType(type), forceModify);
        }
    );
    RemoteCall::exportAs(
        "GMLIB_gmlib::form::ServerSettingForm",
        "addLabel",
        [](std::string const& text, std::string const& detectorId, int priority) -> uint {
            uint result = gmlib::form::ServerSettingForm::addLabel(text, PLAYER_DETECROR, priority);
            return result;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_gmlib::form::ServerSettingForm",
        "addInput",
        [](std::string const& text,
           std::string const& placeholder,
           std::string const& defaultVal,
           std::string const& callbackId,
           std::string const& detectorId,
           int                priority) -> uint {
            uint result = gmlib::form::ServerSettingForm::addInput(
                text,
                placeholder,
                defaultVal,
                CALLBACK_TYPE(std::string const&),
                PLAYER_DETECROR,
                priority
            );
            return result;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_gmlib::form::ServerSettingForm",
        "addToggle",
        [](std::string const& text,
           bool               defaultVal,
           std::string const& callbackId,
           std::string const& detectorId,
           int                priority) -> uint {
            uint result = gmlib::form::ServerSettingForm::addToggle(text, defaultVal, CALLBACK_TYPE(bool), PLAYER_DETECROR, priority);
            return result;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_gmlib::form::ServerSettingForm",
        "addDropdown",
        [](std::string const&       text,
           std::vector<std::string> options,
           int64                    defaultVal,
           std::string const&       callbackId,
           std::string const&       detectorId,
           int                      priority) -> uint {
            uint result = gmlib::form::ServerSettingForm::addDropdown(
                text,
                options,
                defaultVal,
                CALLBACK_TYPE(int64),
                PLAYER_DETECROR,
                priority
            );
            return result;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_gmlib::form::ServerSettingForm",
        "addSlider",
        [](std::string const& text,
           double             min,
           double             max,
           double             step,
           double             defaultVal,
           std::string const& callbackId,
           std::string const& detectorId,
           int                priority) -> uint {
            uint result = gmlib::form::ServerSettingForm::addSlider(
                text,
                min,
                max,
                step,
                defaultVal,
                CALLBACK_TYPE(double),
                PLAYER_DETECROR,
                priority
            );
            return result;
        }
    );
    RemoteCall::exportAs(
        "GMLIB_gmlib::form::ServerSettingForm",
        "addStepSlider",
        [](std::string const&       text,
           std::vector<std::string> steps,
           int64                    defaultVal,
           std::string const&       callbackId,
           std::string const&       detectorId,
           int                      priority) -> uint {
            uint result = gmlib::form::ServerSettingForm::addStepSlider(
                text,
                steps,
                defaultVal,
                CALLBACK_TYPE(int64),
                PLAYER_DETECROR,
                priority
            );
            return result;
        }
    );
    RemoteCall::exportAs("GMLIB_gmlib::form::ServerSettingForm", "removeElement", [](uint id) -> bool {
        return gmlib::form::ServerSettingForm::removeElement(id);
    });
}