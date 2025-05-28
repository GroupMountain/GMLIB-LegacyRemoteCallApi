// // const getNextCallbackId = ll.imports("GMLIB_FormAPI", "getNextFormCallbackId");

// class ServerSettingForm {
//     constructor() {
//         throw new Error("Static class cannot be instantiated");
//     }

//     static getDefaultPriority() {
//         return ll.imports("GMLIB_ServerSettingForm", "getDefaultPriority")();
//     }

//     static hasTitle() {
//         return ll.imports("GMLIB_ServerSettingForm", "hasTitle")();
//     }

//     static getTitle() {
//         return ll.imports("GMLIB_ServerSettingForm", "getTitle")();
//     }

//     static setTitle(title, forceModify = false) {
//         return ll.imports("GMLIB_ServerSettingForm", "setTitle")(title, forceModify);
//     }

//     static hasIcon() {
//         return ll.imports("GMLIB_ServerSettingForm", "hasIcon")();
//     }

//     static getIconData() {
//         return hasIcon() ? ll.imports("GMLIB_ServerSettingForm", "getIconData")() : null;
//     }

//     static getIconType() {
//         return ll.imports("GMLIB_ServerSettingForm", "getIconType")();
//     }

//     static setIcon(data, type = 0, forceModify = false) {
//         return ll.imports("GMLIB_ServerSettingForm", "setIcon")(data, type, forceModify);
//     }

//     static addLabel(
//         text,
//         playerDetector = (pl) => { return true; },
//         priority = this.getDefaultPriority()
//     ) {
//         let detectorId = getNextCallbackId();
//         ll.export(playerDetector, "GMLIB_FORM_CALLBACK", detectorId);
//         return ll.imports("GMLIB_ServerSettingForm", "addLabel")(text, detectorId, priority);
//     }


//     static addInput(
//         text,
//         placeholder,
//         defaultVal,
//         callback = (pl, input) => { },
//         playerDetector = (pl) => { return true; },
//         priority = this.getDefaultPriority()
//     ) {
//         let callbackId = getNextCallbackId();
//         ll.export(callback, "GMLIB_FORM_CALLBACK", callbackId);
//         let detectorId = getNextCallbackId();
//         ll.export(playerDetector, "GMLIB_FORM_CALLBACK", detectorId);
//         return ll.imports("GMLIB_ServerSettingForm", "addInput")(text, placeholder, defaultVal, callbackId, detectorId, priority);
//     }

//     static addToggle(
//         text,
//         defaultVal = false,
//         callback = (pl, input) => { },
//         playerDetector = (pl) => { return true; },
//         priority = this.getDefaultPriority()
//     ) {
//         let callbackId = getNextCallbackId();
//         ll.export(callback, "GMLIB_FORM_CALLBACK", callbackId);
//         let detectorId = getNextCallbackId();
//         ll.export(playerDetector, "GMLIB_FORM_CALLBACK", detectorId);
//         return ll.imports("GMLIB_ServerSettingForm", "addToggle")(text, defaultVal, callbackId, detectorId, priority);
//     }

//     static addDropdown(
//         text,
//         options,
//         defaultVal = 0,
//         callback = (pl, input) => { },
//         playerDetector = (pl) => { return true; },
//         priority = this.getDefaultPriority()
//     ) {
//         let callbackId = getNextCallbackId();
//         ll.export(callback, "GMLIB_FORM_CALLBACK", callbackId);
//         let detectorId = getNextCallbackId();
//         ll.export(playerDetector, "GMLIB_FORM_CALLBACK", detectorId);
//         return ll.imports("GMLIB_ServerSettingForm", "addDropdown")(text, options, defaultVal, callbackId, detectorId, priority);
//     }

//     static addSlider(
//         text,
//         min,
//         max,
//         step = 0.0,
//         defaultVal = 0.0,
//         callback = (pl, input) => { },
//         playerDetector = (pl) => { return true; },
//         priority = this.getDefaultPriority()
//     ) {
//         let callbackId = getNextCallbackId();
//         ll.export(callback, "GMLIB_FORM_CALLBACK", callbackId);
//         let detectorId = getNextCallbackId();
//         ll.export(playerDetector, "GMLIB_FORM_CALLBACK", detectorId);
//         return ll.imports("GMLIB_ServerSettingForm", "addSlider")(text, min, max, step, defaultVal, callbackId, detectorId, priority);
//     }

//     static addStepSlider(
//         text,
//         steps,
//         defaultVal = 0,
//         callback = (pl, input) => { },
//         playerDetector = (pl) => { return true; },
//         priority = this.getDefaultPriority()
//     ) {
//         let callbackId = getNextCallbackId();
//         ll.export(callback, "GMLIB_FORM_CALLBACK", callbackId);
//         let detectorId = getNextCallbackId();
//         ll.export(playerDetector, "GMLIB_FORM_CALLBACK", detectorId);
//         return ll.imports("GMLIB_ServerSettingForm", "addStepSlider")(text, steps, defaultVal, callbackId, detectorId, priority);
//     }

//     static removeElement(id) {
//         return ll.imports("GMLIB_ServerSettingForm", "removeElement")(id);
//     }
// }

// class NpcDialogueForm {
//     constructor(npcName, sceneName, dialogue) {
//         this.mFormId = ll.imports("GMLIB_NpcDialogueForm", "createForm")(npcName, sceneName, dialogue);
//     }

//     addButton(button) {
//         return ll.imports("GMLIB_NpcDialogueForm", "addButton")(this.mFormId, button);
//     }

//     sendTo(pl, callback = (pl, index, type) => { }, free = true) {
//         let callbackId = getNextCallbackId();
//         ll.export(callback, "GMLIB_FORM_CALLBACK", callbackId);
//         ll.imports("GMLIB_NpcDialogueForm", "sendTo")(this.mFormId, pl, callbackId);
//         if (free) {
//             this.destroy();
//         }
//     }

//     destroy() {
//         ll.imports("GMLIB_NpcDialogueForm", "destroyForm")(this.mFormId);
//     }
// }

// class ChestForm {
//     constructor(npcName, sceneName, dialogue) {
//         this.mFormId = ll.imports("GMLIB_NpcDialogueForm", "createForm")(npcName, sceneName, dialogue);
//     }

//     addButton(button) {
//         return ll.imports("GMLIB_NpcDialogueForm", "addButton")(this.mFormId, button);
//     }

//     sendTo(pl, free = true) {
//         //let callbackId = getNextCallbackId();
//         //ll.export(callback, "GMLIB_FORM_CALLBACK", callbackId);
//         //ll.imports("GMLIB_NpcDialogueForm", "sendTo")(this.mFormId, pl, callbackId);
//         //if (free) {
//         //    this.destroy();
//         //}
//     }

//     destroy() {
//         //ll.imports("GMLIB_NpcDialogueForm", "destroyForm")(this.mFormId);
//     }
// }

// module.exports = {
//     ServerSettingForm,
//     NpcDialogueForm,
//     ChestForm
// };