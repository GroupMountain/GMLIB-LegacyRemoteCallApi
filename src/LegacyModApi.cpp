#include "Global.h"

std::unordered_set<std::string> HardCodedKeys = {"AlwaysUnlocked", "PlayerHasManyItems", "PlayerInWater", "None"};

std::variant<std::string, std::vector<RecipeIngredient>> makeRecipeUnlockingKey(std::string const& key) {
    if (HardCodedKeys.count(key)) return key;
    return std::vector<RecipeIngredient>({RecipeIngredient(key, 0, 1)});
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
            if (!gmlib::world::Level::getInstance().has_value()) return;
            std::vector<RecipeIngredient> types;
            for (auto ing : ingredients) {
                types.emplace_back(ing, 0, 1);
            }
            gmlib::mod::recipe::JsonRecipeRegistry::registerShapelessCraftingTableRecipe(
                recipe_id,
                types,
                RecipeIngredient(result, 0, count),
                makeRecipeUnlockingKey(unlock)
            );
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
            if (!gmlib::world::Level::getInstance().has_value()) return;
            std::vector<RecipeIngredient> types;
            for (auto ing : ingredients) {
                types.push_back(RecipeIngredient(ing, 0, 1));
            }
            gmlib::mod::recipe::JsonRecipeRegistry::registerShapedCraftingTableRecipe(
                recipe_id,
                shape,
                types,
                RecipeIngredient(result, 0, count),
                makeRecipeUnlockingKey(unlock)
            );
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerFurnaceRecipe",
        [](std::string const&       recipe_id,
           std::string const&       input,
           std::string const&       output,
           std::vector<std::string> tags) -> void {
            if (!gmlib::world::Level::getInstance().has_value()) return;
            gmlib::mod::recipe::JsonRecipeRegistry::registerFurnaceRecipe(
                recipe_id,
                RecipeIngredient(input, 0, 1),
                RecipeIngredient(output, 0, 1),
                tags
            );
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerBrewingMixRecipe",
        [](std::string const& recipe_id, std::string const& input, std::string const& output, std::string const& reagent
        ) -> void {
            if (!gmlib::world::Level::getInstance().has_value()) return;
            gmlib::mod::recipe::JsonRecipeRegistry::registerBrewingMixRecipe(
                recipe_id,
                input,
                output,
                RecipeIngredient(reagent, 0, 1)
            );
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerBrewingContainerRecipe",
        [](std::string const& recipe_id, std::string const& input, std::string const& output, std::string const& reagent
        ) -> void {
            if (!gmlib::world::Level::getInstance().has_value()) return;
            gmlib::mod::recipe::JsonRecipeRegistry::registerBrewingContainerRecipe(
                recipe_id,
                RecipeIngredient(input, 0, 1),
                RecipeIngredient(output, 0, 1),
                RecipeIngredient(reagent, 0, 1)
            );
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
            if (!gmlib::world::Level::getInstance().has_value()) return;
            gmlib::mod::recipe::JsonRecipeRegistry::registerSmithingTransformRecipe(
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
        [](std::string const& recipe_id,
           std::string const& smithing_template,
           std::string const& base,
           std::string const& addition) -> void {
            if (!gmlib::world::Level::getInstance().has_value()) return;
            gmlib::mod::recipe::JsonRecipeRegistry::registerSmithingTrimRecipe(
                recipe_id,
                smithing_template,
                base,
                addition
            );
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
            if (!gmlib::world::Level::getInstance().has_value()) return;
            gmlib::mod::recipe::JsonRecipeRegistry::registerStoneCutterRecipe(
                recipe_id,
                RecipeIngredient(input, 0, 1),
                RecipeIngredient(output, 0, 1)
            );
        }
    );
    // 错误方块清理
    RemoteCall::exportAs("GMLib_ModAPI", "setUnknownBlockCleaner", []() -> void {
        gmlib::tools::VanillaFix::setAutoCleanUnknownBlockEnabled();
    });
    // 实验性
    RemoteCall::exportAs("GMLib_ModAPI", "registerExperimentsRequire", [](int experiment_id) -> void {
        auto                               list = gmlib::world::Level::getAllExperiments();
        std::unordered_set<AllExperiments> set(list.begin(), list.end());
        if (set.contains((AllExperiments)experiment_id)) {
            gmlib::world::Level::addExperimentsRequire((AllExperiments)experiment_id);
        } else {
            ll::Logger("Server").error("Experiment ID '{}' does not exist!", experiment_id);
        }
    });
    RemoteCall::exportAs("GMLib_ModAPI", "setExperimentEnabled", [](int experiment_id, bool value) -> void {
        if (gmlib::world::Level::getInstance()) {
            auto                               list = gmlib::world::Level::getAllExperiments();
            std::unordered_set<AllExperiments> set(list.begin(), list.end());
            if (set.contains((AllExperiments)experiment_id)) {
                gmlib::world::Level::getInstance()->setExperimentEnabled(((AllExperiments)experiment_id), value);
            } else ll::Logger("Server").error("Experiment ID '{}' does not exist!", experiment_id);
        }
    });
    RemoteCall::exportAs("GMLib_ModAPI", "getExperimentEnabled", [](int experiment_id) -> bool {
        if (gmlib::world::Level::getInstance()) {
            auto                               list = gmlib::world::Level::getAllExperiments();
            std::unordered_set<AllExperiments> set(list.begin(), list.end());
            if (set.contains((AllExperiments)experiment_id)) {
                return gmlib::world::Level::getInstance()->getExperimentEnabled(((AllExperiments)experiment_id));
            }
            ll::Logger("Server").error("Experiment ID '{}' does not exist!", experiment_id);
        }
        return false;
    });
    RemoteCall::exportAs("GMLib_ModAPI", "setFixI18nEnabled", []() -> void {
        gmlib::tools::VanillaFix::setFixI18nEnabled();
    });
}