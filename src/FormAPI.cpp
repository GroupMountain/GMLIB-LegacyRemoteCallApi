#include "Global.h"
#include "gmlib/world/Player.h"

using namespace gmlib::form;
using namespace ll::hash_utils;

class LegacyScriptFormManager {
private:
    int64                                                       mNextFormCallbackId = 0;
    int64                                                       mNextFormId         = 0;
    std::unordered_map<int64, std::unique_ptr<NpcDialogueForm>> mNpcDialogueForms;
    // std::unordered_map<int64, std::unique_ptr<ChestForm>>       mChestForms;

public:
    std::string getNextFormCallbackId() {
        mNextFormCallbackId++;
        return "GMLIB_EVENT_" + std::to_string(mNextFormCallbackId);
    }

    int64 getNextFormId() {
        mNextFormId++;
        return mNextFormId;
    }

    int64 createNpcDialogueForm(std::string const& npcName, std::string const& sceneName, std::string const& dialogue) {
        auto formId               = LegacyScriptFormManager::getInstance().getNextFormId();
        auto formPtr              = std::make_unique<NpcDialogueForm>(npcName, sceneName, dialogue);
        mNpcDialogueForms[formId] = std::move(formPtr);
        return formId;
    }

    bool destroyNpcDialogueForm(int64 formId) {
        if (mNpcDialogueForms.contains(formId)) {
            mNpcDialogueForms.erase(formId);
            return true;
        }
        return false;
    }

    optional_ref<NpcDialogueForm> getNpcDialogueForm(int64 formId) {
        if (mNpcDialogueForms.contains(formId)) {
            return mNpcDialogueForms[formId].get();
        }
        return {};
    }

    /*
    int64 createChestForm(std::string const& npcName, std::string const& sceneName, std::string const& dialogue) {
        auto formId         = LegacyScriptFormManager::getInstance().getNextFormId();
        auto formPtr        = std::make_unique<ChestForm>(npcName, sceneName, dialogue);
        mChestForms[formId] = std::move(formPtr);
        return formId;
    }

    bool destroyChestForm(int64 formId) {
        if (mChestForms.contains(formId)) {
            mChestForms.erase(formId);
            return true;
        }
        return false;
    }

    optional_ref<ChestForm> getChestForm(int64 formId) {
        if (mChestForms.contains(formId)) {
            return mChestForms[formId].get();
        }
        return {};
    }

    */
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
    [detectorId, result](::Player& pl) -> bool {                                                                       \
        try {                                                                                                          \
            if (RemoteCall::hasFunc("GMLIB_FORM_CALLBACK", detectorId)) {                                              \
                auto const& detector = RemoteCall::importAs<bool(::Player*)>("GMLIB_FORM_CALLBACK", detectorId);       \
                return detector(&pl);                                                                                  \
            } else {                                                                                                   \
                ServerSettingForm::removeElement(result);                                                              \
            }                                                                                                          \
        } catch (...) {}                                                                                               \
        return false;                                                                                                  \
    }

#define CALLBACK_TYPE_STRING                                                                                           \
    [callbackId, result](::Player& pl, std::string const& data) {                                                      \
        try {                                                                                                          \
            if (RemoteCall::hasFunc("GMLIB_FORM_CALLBACK", callbackId)) {                                              \
                auto const& callback =                                                                                 \
                    RemoteCall::importAs<void(::Player*, std::string const&)>("GMLIB_FORM_CALLBACK", callbackId);      \
                callback(&pl, data);                                                                                   \
            } else {                                                                                                   \
                ServerSettingForm::removeElement(result);                                                              \
            }                                                                                                          \
        } catch (...) {}                                                                                               \
    }

#define CALLBACK_TYPE_BOOL                                                                                             \
    [callbackId, result](::Player& pl, bool data) {                                                                    \
        try {                                                                                                          \
            if (RemoteCall::hasFunc("GMLIB_FORM_CALLBACK", callbackId)) {                                              \
                auto const& callback = RemoteCall::importAs<void(::Player*, bool)>("GMLIB_FORM_CALLBACK", callbackId); \
                callback(&pl, data);                                                                                   \
            } else {                                                                                                   \
                ServerSettingForm::removeElement(result);                                                              \
            }                                                                                                          \
        } catch (...) {}                                                                                               \
    }

#define CALLBACK_TYPE_DOUBLE                                                                                           \
    [callbackId, result](::Player& pl, double data) {                                                                  \
        try {                                                                                                          \
            if (RemoteCall::hasFunc("GMLIB_FORM_CALLBACK", callbackId)) {                                              \
                auto const& callback =                                                                                 \
                    RemoteCall::importAs<void(::Player*, double)>("GMLIB_FORM_CALLBACK", callbackId);                  \
                callback(&pl, data);                                                                                   \
            } else {                                                                                                   \
                ServerSettingForm::removeElement(result);                                                              \
            }                                                                                                          \
        } catch (...) {}                                                                                               \
    }


#define CALLBACK_TYPE_LONG                                                                                             \
    [callbackId, result](::Player& pl, int64 data) {                                                                   \
        try {                                                                                                          \
            if (RemoteCall::hasFunc("GMLIB_FORM_CALLBACK", callbackId)) {                                              \
                auto const& callback =                                                                                 \
                    RemoteCall::importAs<void(::Player*, int64)>("GMLIB_FORM_CALLBACK", callbackId);                   \
                callback(&pl, data);                                                                                   \
            } else {                                                                                                   \
                ServerSettingForm::removeElement(result);                                                              \
            }                                                                                                          \
        } catch (...) {}                                                                                               \
    }

#define CALLBACK_TYPE_NORMAL                                                                                           \
    [callbackId](::Player& pl) {                                                                                       \
        try {                                                                                                          \
            if (RemoteCall::hasFunc("GMLIB_FORM_CALLBACK", callbackId)) {                                              \
                auto const& callback = RemoteCall::importAs<void(::Player*)>("GMLIB_FORM_CALLBACK", callbackId);       \
                callback(&pl);                                                                                         \
            }                                                                                                          \
        } catch (...) {}                                                                                               \
    }


void Export_Form_API() {
    ////////////////////////////////   Form Manager   /////////////////////////////////
    RemoteCall::exportAs("GMLIB_FormAPI", "getNextFormCallbackId", []() -> std::string {
        return LegacyScriptFormManager::getInstance().getNextFormCallbackId();
    });
    //////////////////////////////   ServerSettingForm   //////////////////////////////
    RemoteCall::exportAs("GMLIB_ServerSettingForm", "getDefaultPriority", []() -> int {
        return ServerSettingForm::getDefaultPriority();
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
    //////////////////////////////   NpcDialogueForm   //////////////////////////////
    RemoteCall::exportAs(
        "GMLIB_NpcDialogueForm",
        "createForm",
        [](std::string const& npcName, std::string const& sceneName, std::string const& dialogue) -> int64 {
            return LegacyScriptFormManager::getInstance().createNpcDialogueForm(npcName, sceneName, dialogue);
        }
    );
    RemoteCall::exportAs("GMLIB_NpcDialogueForm", "destroyForm", [](int64 formId) -> bool {
        return LegacyScriptFormManager::getInstance().destroyNpcDialogueForm(formId);
    });
    RemoteCall::exportAs(
        "GMLIB_NpcDialogueForm",
        "addButton",
        [](int64 formId, std::string const& button, std::string const& callbackId) -> void {
            if (auto formPtr = LegacyScriptFormManager::getInstance().getNpcDialogueForm(formId)) {
                formPtr->addButton(button, CALLBACK_TYPE_NORMAL);
            }
        }
    );
    RemoteCall::exportAs(
        "GMLIB_NpcDialogueForm",
        "onPlayerClose",
        [](int64 formId, std::string const& callbackId) -> void {
            if (auto formPtr = LegacyScriptFormManager::getInstance().getNpcDialogueForm(formId)) {
                formPtr->onPlayerClose(CALLBACK_TYPE_NORMAL);
            }
        }
    );
    RemoteCall::exportAs("GMLIB_NpcDialogueForm", "sendTo", [](int64 formId, ::Player* pl) -> void {
        if (auto formPtr = LegacyScriptFormManager::getInstance().getNpcDialogueForm(formId)) {
            formPtr->sendTo(*pl);
        }
    });
    //////////////////////////////   ChestForm   //////////////////////////////
}