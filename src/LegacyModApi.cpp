#include "Global.h"

std::unordered_set<std::string> HardCodedKeys = {"AlwaysUnlocked", "PlayerHasManyItems", "PlayerInWater", "None"};

std::variant<std::string, std::vector<RecipeIngredient>> makeRecipeUnlockingKey(std::string const& key) {
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
        [](std::string const&       recipe_id,
           std::vector<std::string> ingredients,
           std::string const&       result,
           int                      count,
           std::string const&       unlock) -> void {
            auto level = world::Level::getInstance();
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
            recipe::JsonRecipeRegistry::registerShapelessCraftingTableRecipe(recipe_id, types, res, unl);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerShapedRecipe",
        [](std::string const&       recipe_id,
           std::vector<std::string> shape,
           std::vector<std::string> ingredients,
           std::string const&       result,
           int                      count,
           std::string const&       unlock) -> void {
            auto level = world::Level::getInstance();
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
            recipe::JsonRecipeRegistry::registerShapedCraftingTableRecipe(recipe_id, shape, types, res, unl);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerFurnaceRecipe",
        [](std::string const&       recipe_id,
           std::string const&       input,
           std::string const&       output,
           std::vector<std::string> tags) -> void {
            auto level = world::Level::getInstance();
            if (!level) {
                return;
            }
            auto inp  = RecipeIngredient(input, 0, 1);
            auto outp = RecipeIngredient(output, 0, 1);
            recipe::JsonRecipeRegistry::registerFurnaceRecipe(recipe_id, inp, outp, tags);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerBrewingMixRecipe",
        [](std::string const& recipe_id, std::string const& input, std::string const& output, std::string const& reagent
        ) -> void {
            auto level = world::Level::getInstance();
            if (!level) {
                return;
            }
            auto rea = RecipeIngredient(reagent, 0, 1);
            recipe::JsonRecipeRegistry::registerBrewingMixRecipe(recipe_id, input, output, rea);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerBrewingContainerRecipe",
        [](std::string const& recipe_id, std::string const& input, std::string const& output, std::string const& reagent
        ) -> void {
            auto level = world::Level::getInstance();
            if (!level) {
                return;
            }
            auto inp  = RecipeIngredient(input, 0, 1);
            auto outp = RecipeIngredient(output, 0, 1);
            auto rea  = RecipeIngredient(reagent, 0, 1);
            recipe::JsonRecipeRegistry::registerBrewingContainerRecipe(recipe_id, inp, outp, rea);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerSmithingTransformRecipe",
        [](std::string const& recipe_id,
           std::string const& smithing_template,
           std::string const& base,
           std::string const& addition,
           std::string const& result) -> void {
            auto level = world::Level::getInstance();
            if (!level) {
                return;
            }
            recipe::JsonRecipeRegistry::registerSmithingTransformRecipe(recipe_id, smithing_template, base, addition, result);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerSmithingTrimRecipe",
        [](std::string const& recipe_id,
           std::string const& smithing_template,
           std::string const& base,
           std::string const& addition) -> void {
            auto level = world::Level::getInstance();
            if (!level) {
                return;
            }
            recipe::JsonRecipeRegistry::registerSmithingTrimRecipe(recipe_id, smithing_template, base, addition);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerStoneCutterRecipe",
        [](std::string const& recipe_id,
           std::string const& input,
           int                input_data,
           std::string const& output,
           int                output_data,
           int                output_count) -> void {
            auto level = world::Level::getInstance();
            if (!level) {
                return;
            }
            auto inp  = RecipeIngredient(input, 0, 1);
            auto outp = RecipeIngredient(output, 0, 1);
            recipe::JsonRecipeRegistry::registerStoneCutterRecipe(recipe_id, inp, outp);
        }
    );
    // 错误方块清理
    RemoteCall::exportAs("GMLib_ModAPI", "setUnknownBlockCleaner", []() -> void {
        VanillaFix::setAutoCleanUnknownBlockEnabled();
    });
    // 实验性
    RemoteCall::exportAs("GMLib_ModAPI", "registerExperimentsRequire", [](int experiment_id) -> void {
        auto                               list = world::Level::getAllExperiments();
        std::unordered_set<AllExperiments> set(list.begin(), list.end());
        if (set.contains((AllExperiments)experiment_id)) {
            world::Level::addExperimentsRequire((AllExperiments)experiment_id);
        } else {
            ll::Logger("Server").error("Experiment ID '{}' does not exist!", experiment_id);
        }
    });
    RemoteCall::exportAs("GMLib_ModAPI", "setExperimentEnabled", [](int experiment_id, bool value) -> void {
        if (world::Level::getInstance()) {
            auto                               list = world::Level::getAllExperiments();
            std::unordered_set<AllExperiments> set(list.begin(), list.end());
            if (set.contains((AllExperiments)experiment_id)) {
                world::Level::getInstance()->setExperimentEnabled(((AllExperiments)experiment_id), value);
            } else ll::Logger("Server").error("Experiment ID '{}' does not exist!", experiment_id);
        }
    });
    RemoteCall::exportAs("GMLib_ModAPI", "getExperimentEnabled", [](int experiment_id) -> bool {
        if (world::Level::getInstance()) {
            auto                               list = world::Level::getAllExperiments();
            std::unordered_set<AllExperiments> set(list.begin(), list.end());
            if (set.contains((AllExperiments)experiment_id)) {
                return world::Level::getInstance()->getExperimentEnabled(((AllExperiments)experiment_id));
            } else {
                ll::Logger("Server").error("Experiment ID '{}' does not exist!", experiment_id);
                return false;
            }
        }
        return false;
    });
    RemoteCall::exportAs("GMLib_ModAPI", "setFixI18nEnabled", []() -> void { VanillaFix::setFixI18nEnabled(); });
}