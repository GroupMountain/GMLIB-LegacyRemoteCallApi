#include "Global.h"

std::unordered_set<std::string> HardCodedKeys = {"AlwaysUnlocked", "PlayerHasManyItems", "PlayerInWater", "None"};

ICustomRecipe::UnlockingRequirement makeRecipeUnlockingKey(std::string const& key) {
    if (HardCodedKeys.count(key)) return {{ICustomRecipe::Ingredient{key}}};
    return ICustomRecipe::UnlockingRequirement({ICustomRecipe::Ingredient(key, 1, 0)});
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
            if (!GMLevel::getInstance().has_value()) return;
            std::vector<ICustomRecipe::Ingredient> types;
            for (auto& ing : ingredients) {
                types.emplace_back(ICustomRecipe::Ingredient{ing, 1});
            }
            CustomRecipeRegistry::getInstance()
                .registerShapelessRecipe(recipe_id, types, ItemInstance(result, count), makeRecipeUnlockingKey(unlock));
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
            if (!GMLevel::getInstance().has_value()) return;
            ICustomShapedRecipe::ShapedIngredients types;
            char                                   index = 'a';
            for (auto& ing : ingredients) {
                types.add(std::string{index++}, ICustomRecipe::Ingredient{ing, 1});
            }
            CustomRecipeRegistry::getInstance().registerShapedRecipe(
                recipe_id,
                shape,
                types,
                ItemInstance(result, count),
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
            if (!GMLevel::getInstance().has_value()) return;
            CustomRecipeRegistry::getInstance()
                .registerFurnaceRecipe(ICustomRecipe::Ingredient{input}, ItemInstance{output}, tags);
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerBrewingMixRecipe",
        [](std::string const& recipe_id, std::string const& input, std::string const& output, std::string const& reagent
        ) -> void {
            if (!GMLevel::getInstance().has_value()) return;
            CustomRecipeRegistry::getInstance().registerBrewingRecipe(
                ICustomRecipe::Ingredient{input},
                ICustomRecipe::Ingredient{reagent},
                ICustomRecipe::Ingredient{output}
            );
        }
    );
    RemoteCall::exportAs(
        "GMLib_ModAPI",
        "registerBrewingContainerRecipe",
        [](std::string const& recipe_id, std::string const& input, std::string const& output, std::string const& reagent
        ) -> void {
            if (!GMLevel::getInstance().has_value()) return;
            CustomRecipeRegistry::getInstance().registerBrewingRecipe(
                ICustomRecipe::Ingredient{input},
                ICustomRecipe::Ingredient{reagent},
                ICustomRecipe::Ingredient{output}
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
            if (!GMLevel::getInstance().has_value()) return;
            CustomRecipeRegistry::getInstance().registerSmithingTransformRecipe(
                recipe_id,
                ICustomRecipe::Ingredient{smithing_template},
                ICustomRecipe::Ingredient{base},
                ICustomRecipe::Ingredient{addition},
                ItemInstance{result}
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
            if (!GMLevel::getInstance().has_value()) return;
            CustomRecipeRegistry::getInstance().registerSmithingTrimRecipe(
                recipe_id,
                ICustomRecipe::Ingredient{smithing_template},
                ICustomRecipe::Ingredient{base},
                ICustomRecipe::Ingredient{addition}
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
            if (!GMLevel::getInstance().has_value()) return;
            CustomRecipeRegistry::getInstance().registerStoneCutterRecipe(
                recipe_id,
                ICustomRecipe::Ingredient{input, 1, input_data},
                {output, output_count, output_data}
            );
        }
    );
    // 错误方块清理
    RemoteCall::exportAs("GMLib_ModAPI", "setUnknownBlockCleaner", []() -> void {
        getLogger().error("setUnknownBlockCleaner is not implemented");
    });
    // 实验性
    RemoteCall::exportAs("GMLib_ModAPI", "registerExperimentsRequire", [](int experiment_id) -> void {
        GMLevel::getInstance().and_then([&](GMLevel& level) {
            level.setExperimentEnabled((AllExperiments)experiment_id);
            return true;
        });
    });
    RemoteCall::exportAs("GMLib_ModAPI", "setExperimentEnabled", [](int experiment_id, bool value) -> void {
        GMLevel::getInstance().and_then([&](GMLevel& level) {
            level.setExperimentEnabled((AllExperiments)experiment_id, value);
            return true;
        });
    });
    RemoteCall::exportAs("GMLib_ModAPI", "getExperimentEnabled", [](int experiment_id) -> bool {
        return GMLevel::getInstance()
            .transform([&](GMLevel& level) { return level.getExperimentEnabled((AllExperiments)experiment_id); })
            .value_or(false);
    });
    RemoteCall::exportAs("GMLib_ModAPI", "setFixI18nEnabled", []() -> void {});
}