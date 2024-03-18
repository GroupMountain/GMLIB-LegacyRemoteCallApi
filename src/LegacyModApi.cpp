#include "Global.h"

std::unordered_set<std::string> HardCodedKeys = {"AlwaysUnlocked", "PlayerHasManyItems", "PlayerInWater", "None"};

std::variant<std::string, std::vector<RecipeIngredient>> makeRecipeUnlockingKey(std::string& key) {
    if (HardCodedKeys.count(key)) {
        return key;
    }
    std::vector<RecipeIngredient> result;
    auto                          item = RecipeIngredient(key, 0, 1);
    result.emplace_back(item);
    return result;
}

void Export_Legacy_GMLib_ModAPI() {
    // 合成表部分
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerShapelessRecipe",
        [](std::string              recipe_id,
           std::vector<std::string> ingredients,
           std::string              result,
           int                      count,
           std::string              unlock) -> void {
            auto level = GMLIB_Level::getLevel();
            if (!level) {
                return;
            }
            std::vector<RecipeIngredient> types;
            for (auto ing : ingredients) {
                auto key = RecipeIngredient(ing, 0, 1);
                types.push_back(key);
            }
            auto res = RecipeIngredient(result, 0, count);
            auto unl = makeRecipeUnlockingKey(unlock);
            GMLIB::Mod::JsonRecipe::registerShapelessCraftingTableRecipe(recipe_id, types, res, unl);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerShapedRecipe",
        [](std::string              recipe_id,
           std::vector<std::string> shape,
           std::vector<std::string> ingredients,
           std::string              result,
           int                      count,
           std::string              unlock) -> void {
            auto level = GMLIB_Level::getLevel();
            if (!level) {
                return;
            }
            std::vector<RecipeIngredient> types;
            for (auto ing : ingredients) {
                auto key = RecipeIngredient(ing, 0, 1);
                types.push_back(key);
            }
            auto res = RecipeIngredient(result, 0, count);
            auto unl = makeRecipeUnlockingKey(unlock);
            GMLIB::Mod::JsonRecipe::registerShapedCraftingTableRecipe(recipe_id, shape, types, res, unl);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerFurnaceRecipe",
        [](std::string recipe_id, std::string input, std::string output, std::vector<std::string> tags) -> void {
            auto level = GMLIB_Level::getLevel();
            if (!level) {
                return;
            }
            auto inp  = RecipeIngredient(input, 0, 1);
            auto outp = RecipeIngredient(output, 0, 1);
            GMLIB::Mod::JsonRecipe::registerFurnaceRecipe(recipe_id, inp, outp, tags);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerBrewingMixRecipe",
        [](std::string recipe_id, std::string input, std::string output, std::string reagent) -> void {
            auto level = GMLIB_Level::getLevel();
            if (!level) {
                return;
            }
            auto rea = RecipeIngredient(reagent, 0, 1);
            GMLIB::Mod::JsonRecipe::registerBrewingMixRecipe(recipe_id, input, output, rea);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerBrewingContainerRecipe",
        [](std::string recipe_id, std::string input, std::string output, std::string reagent) -> void {
            auto level = GMLIB_Level::getLevel();
            if (!level) {
                return;
            }
            auto inp  = RecipeIngredient(input, 0, 1);
            auto outp = RecipeIngredient(output, 0, 1);
            auto rea  = RecipeIngredient(reagent, 0, 1);
            GMLIB::Mod::JsonRecipe::registerBrewingContainerRecipe(recipe_id, inp, outp, rea);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerSmithingTransformRecipe",
        [](std::string recipe_id,
           std::string smithing_template,
           std::string base,
           std::string addition,
           std::string result) -> void {
            auto level = GMLIB_Level::getLevel();
            if (!level) {
                return;
            }
            GMLIB::Mod::JsonRecipe::registerSmithingTransformRecipe(
                recipe_id,
                smithing_template,
                base,
                addition,
                result
            );
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerSmithingTrimRecipe",
        [](std::string recipe_id, std::string smithing_template, std::string base, std::string addition) -> void {
            auto level = GMLIB_Level::getLevel();
            if (!level) {
                return;
            }
            GMLIB::Mod::JsonRecipe::registerSmithingTrimRecipe(recipe_id, smithing_template, base, addition);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerStoneCutterRecipe",
        [](std::string recipe_id,
           std::string input,
           int         input_data,
           std::string output,
           int         output_data,
           int         output_count) -> void {
            auto level = GMLIB_Level::getLevel();
            if (!level) {
                return;
            }
            auto inp  = RecipeIngredient(input, 0, 1);
            auto outp = RecipeIngredient(output, 0, 1);
            GMLIB::Mod::JsonRecipe::registerStoneCutterRecipe(recipe_id, inp, outp);
        }
    );
    // 错误方块清理
    RemoteCall::exportAs("GMLib_ModAPI", "setUnknownBlockCleaner", []() -> void {
        GMLIB::Mod::VanillaFix::setAutoCleanUnknownBlockEnabled();
    });
    // 实验性
    RemoteCall::exportAs("GMLib_ModAPI", "registerExperimentsRequire", [](int experiment_id) -> void {
        auto map = GMLIB_Level::getAllExperiments();
        if (map.count(experiment_id)) {
            GMLIB_Level::addExperimentsRequire((AllExperiments)experiment_id);
        } else {
            ll::Logger("Server").error("Experiment ID '{}' does not exist!", experiment_id);
        }
    });
    RemoteCall::exportAs("GMLib_ModAPI", "setExperimentEnabled", [](int experiment_id, bool value) -> void {
        auto level = GMLIB_Level::getLevel();
        if (!level) {
            return;
        }
        auto map = GMLIB_Level::getAllExperiments();
        if (map.count(experiment_id)) {
            GMLIB_Level::getLevel()->setExperimentEnabled(((AllExperiments)experiment_id), value);
        } else ll::Logger("Server").error("Experiment ID '{}' does not exist!", experiment_id);
    });
    RemoteCall::exportAs("GMLib_ModAPI", "getExperimentEnabled", [](int experiment_id) -> bool {
        auto level = GMLIB_Level::getLevel();
        if (!level) {
            return false;
        }
        auto map = GMLIB_Level::getAllExperiments();
        if (map.count(experiment_id)) {
            return GMLIB_Level::getLevel()->getExperimentEnabled(((AllExperiments)experiment_id));
        } else {
            ll::Logger("Server").error("Experiment ID '{}' does not exist!", experiment_id);
            return false;
        }
    });
}