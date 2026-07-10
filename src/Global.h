#pragma once
// clang-format off
#pragma warning(push)
#pragma warning(disable : 4996)
#pragma include_alias("mc/world/item/HumanoidArmorItem.h", "modapi/item/types/mc/HumanoidArmorItem.h")
// ll/api
#include <ll/api/base/Containers.h>
#include <ll/api/base/StdInt.h>
#include <ll/api/base/TypeTraits.h>
#include <ll/api/data/Version.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/Listener.h>
#include <ll/api/event/server/ServerStoppingEvent.h>
#include <ll/api/io/Logger.h>
#include <ll/api/io/LoggerRegistry.h>
#include <ll/api/mod/ModManagerRegistry.h>
#include <ll/api/reflection/Reflection.h>
#include <ll/api/service/Bedrock.h>
#include <ll/api/thread/ThreadPoolExecutor.h>
#include <ll/api/utils/HashUtils.h>
#include <ll/api/utils/StringUtils.h>

// gmlib shared
#include <gmlib/Macros.h>
#include <gmlib/Version.h>
#include <gmlib/gm/data/TpsStatus.h>
#include <gmlib/gm/data/UserCache.h>
#include <gmlib/gm/economics/EconomicsEvents.h>
#include <gmlib/gm/economics/EconomicsSystem.h>
#include <gmlib/gm/economics/EconomicsSystemManager.h>
#include <gmlib/gm/enum/ChestType.h>
#include <gmlib/gm/enum/PlayerListType.h>
#include <gmlib/gm/floating_text/FloatingTextManager.h>
#include <gmlib/gm/floating_text/base/DynamicFloatingText.h>
#include <gmlib/gm/floating_text/base/FloatingText.h>
#include <gmlib/gm/floating_text/base/StaticFloatingText.h>
#include <gmlib/gm/papi/PlaceholderAPI.h>
#include <gmlib/gm/ui/ChestForm.h>
#include <gmlib/gm/ui/ChestUI.h>
#include <gmlib/gm/ui/CustomForm.h>
#include <gmlib/gm/ui/NpcDialogueForm.h>
#include <gmlib/gm/ui/PlayerListAPI.h>
#include <gmlib/gm/ui/ServerSettingForm.h>

// gmlib static
#include <gmlib/gm/GlobalUsing.h>
#include <gmlib/gm/enum/CompressionLevel.h>
#include <gmlib/gm/enum/FillMode.h>
#include <gmlib/gm/enum/WeatherType.h>
#include <gmlib/gm/i18n/JsonI18n.h>
#include <gmlib/gm/i18n/LangI18n.h>
#include <gmlib/gm/i18n/ResourceI18n.h>
#include <gmlib/gm/i18n/base/JsonLanguage.h>
#include <gmlib/gm/i18n/base/LangLanguage.h>
#include <gmlib/gm/i18n/base/McLang.h>
#include <gmlib/gm/io/FileUtils.h>
#include <gmlib/gm/io/JsonUtils.h>
#include <gmlib/gm/io/ZipUtils.h>
#include <gmlib/gm/memory/Compression.h>
#include <gmlib/gm/memory/Function.h>
#include <gmlib/gm/memory/MemoryArchive.h>
#include <gmlib/gm/memory/Resource.h>
#include <gmlib/gm/utils/FlagEnum.h>
#include <gmlib/gm/utils/StringUtils.h>
#include <gmlib/gm/utils/SystemUtils.h>
#include <gmlib/mc/locale/I18nAPI.h>
#include <gmlib/mc/network/BinaryStream.h>
#include <gmlib/mc/world/CompoundTag.h>
#include <gmlib/mc/world/ItemStack.h>
#include <gmlib/mc/world/Level.h>
#include <gmlib/mc/world/Scoreboard.h>
#include <gmlib/mc/world/Spawner.h>
#include <gmlib/mc/world/actor/Actor.h>
#include <gmlib/mc/world/actor/OfflinePlayer.h>
#include <gmlib/mc/world/actor/Player.h>
#include <gmlib/mc/world/actor/UnloadedActor.h>

// mc
#include <mc/entity/components_json_legacy/RideableComponent.h>
#include <mc/legacy/ActorRuntimeID.h>
#include <mc/network/packet/InventorySlotPacket.h>
#include <mc/network/packet/InventorySlotPacketPayload.h>
#include <mc/network/packet/SetSpawnPositionPacket.h>
#include <mc/network/packet/SpawnPositionType.h>
#include <mc/world/actor/ActorDamageSource.h>
#include <mc/world/actor/ActorHurtResult.h>
#include <mc/world/actor/item/ItemActor.h>
#include <mc/world/attribute/AttributeBuff.h>
#include <mc/world/attribute/AttributeInstance.h>
#include <mc/world/attribute/AttributeInstanceConstRef.h>
#include <mc/world/inventory/network/ItemStackRequestSlotInfo.h>
#include <mc/world/item/crafting/RecipeIngredient.h>
#include <mc/world/item/crafting/Recipes.h>
#include <mc/world/item/crafting/RecipeUnlockingRequirement.h>
#include <mc/world/item/enchanting/EnchantUtils.h>
#include <mc/world/effect/MobEffect.h>
#include <mc/world/effect/MobEffectInstance.h>
#include <mc/world/level/dimension/VanillaDimensions.h>
#include <mc/world/level/storage/LevelData.h>
#include <mc/world/level/storage/LevelDataValue.h>
#include <mc/world/scores/Objective.h>

// LegacyMoney & LegacyRemoteCall
#include <LegacyMoney/LegacyMoney.h>
#include <LegacyRemoteCall/RemoteCallAPI.h>

// ila events
#include <ila/event/minecraft/server/ClientLoginEvent.h>
#include <ila/event/minecraft/world/SpawnItemActorEvent.h>
#include <ila/event/minecraft/world/SpawnWanderingTraderEvent.h>
#include <ila/event/minecraft/world/actor/ActorChangeDimensionEvent.h>
#include <ila/event/minecraft/world/actor/ActorPickupItemEvent.h>
#include <ila/event/minecraft/world/actor/DeathMessageEvent.h>
#include <ila/event/minecraft/world/actor/DragonRespawnEvent.h>
#include <ila/event/minecraft/world/actor/MobHealthChangeEvent.h>
#include <ila/event/minecraft/world/actor/MobTakeBlockEvent.h>
#include <ila/event/minecraft/world/actor/ProjectileCreateEvent.h>
#include <ila/event/minecraft/world/actor/player/PlayerCloseContainerEvent.h>
#include <ila/event/minecraft/world/actor/player/PlayerRequestItemActionEvent.h>
#include <ila/event/minecraft/world/actor/player/PlayerStartSleepEvent.h>
#include <ila/event/minecraft/world/actor/player/PlayerStopSleepEvent.h>
#include <ila/event/minecraft/world/level/WeatherUpdateEvent.h>

// modapi
#include <modapi/addons/AddonsLoader.h>
#include <modapi/item/CustomItemRegistry.h>
#include <modapi/recipe/CustomRecipeRegistry.h>
#include <RemoteCallAPI.h>
using namespace gmlib;
using namespace gmlib::ui;
using namespace gmlib::i18n;
using namespace gmlib::memory;
using namespace modapi;
#pragma warning(pop)
// clang-format on

#define PLUGIN_NAME fmt::format(fg(fmt::color::light_green), "GMLIB-LRCA")

#define LIB_VERSION_MAJOR    1
#define LIB_VERSION_MINOR    8
#define LIB_VERSION_PATCH    0
#define LIB_VERSION_PRERELEASE std::nullopt

#ifdef LIB_VERSION_PRERELEASE
#define LIB_VERSION ll::data::Version(LIB_VERSION_MAJOR, LIB_VERSION_MINOR, LIB_VERSION_PATCH, LIB_VERSION_PRERELEASE)
#else
#define LIB_VERSION ll::data::Version(LIB_VERSION_MAJOR, LIB_VERSION_MINOR, LIB_VERSION_PATCH)
#endif

extern void                                  Export_Legacy_GMLib_ModAPI();
extern void                                  Export_Legacy_GMLib_ServerAPI();
extern void                                  Export_Compatibility_API();
extern void                                  ExportPAPI();
extern void                                  Export_Event_API();
extern void                                  Export_BinaryStream_API();
extern ll::thread::ThreadPoolExecutor const& getThreadPoolExecutor();
extern ll::io::Logger&                       getLogger();
// extern void Export_Form_API();


template <>
struct fmt::formatter<ActorUniqueID> : fmt::formatter<int64> {
    template <class FormatContext>
    auto format(ActorUniqueID const& t, FormatContext& ctx) const {
        return formatter<int64>::format(t.rawID, ctx);
    }
};
template <>
struct fmt::formatter<mce::UUID> : fmt::formatter<std::string> {
    template <class FormatContext>
    auto format(mce::UUID const& t, FormatContext& ctx) const {
        return formatter<std::string>::format(t.asString(), ctx);
    }
};