#include "Global.h"

using namespace ll::hash_utils;

class LegacyScriptFormManager {
private:
    int64                                                       mNextFormCallbackId = 0;
    int64                                                       mNextFormId         = 0;
    std::unordered_map<int64, std::unique_ptr<gmlib::form::NpcDialogueForm>> mNpcDialogueForms;
    // std::unordered_map<int64, std::unique_ptr<ChestForm>>       mChestForms;

public:
    //     std::string getNextFormCallbackId() {
    //         return "GMLIB_FormApi_" + std::to_string(mNextFormCallbackId++);
    //     }

    int64 getNextFormId() {
        mNextFormId++;
        return mNextFormId;
    }

    int64 createNpcDialogueForm(std::string const& npcName, std::string const& sceneName, std::string const& dialogue) {
        auto formId               = LegacyScriptFormManager::getInstance().getNextFormId();
        auto formPtr              = std::make_unique<gmlib::form::NpcDialogueForm>(npcName, sceneName, dialogue);
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

    optional_ref<gmlib::form::NpcDialogueForm> getNpcDialogueForm(int64 formId) {
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
    // RemoteCall::exportAs("GMLIB_FormAPI", "getNextFormCallbackId", []() -> std::string {
    //     return LegacyScriptFormManager::getInstance().getNextFormCallbackId();
    // });
    //////////////////////////////   ServerSettingForm   //////////////////////////////
    RemoteCall::exportAs("GMLIB_ServerSettingForm", "getDefaultPriority", []() -> int {
        return gmlib::form::ServerSettingForm::getDefaultPriority();
    });
    RemoteCall::exportAs("GMLIB_ServerSettingForm", "hasTitle", []() -> bool { return gmlib::form::ServerSettingForm::hasTitle(); });
    RemoteCall::exportAs("GMLIB_ServerSettingForm", "getTitle", []() -> std::string {
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