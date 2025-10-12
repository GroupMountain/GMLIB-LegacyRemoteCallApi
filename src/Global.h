#pragma once
// clang-format off
#pragma warning(push)
#pragma warning(disable : 4996)
#pragma include_alias("mc/world/item/HumanoidArmorItem.h", "modapi/item/types/mc/HumanoidArmorItem.h")
#include <gmlib/include_ll.h>
#include <gmlib/include_lib.h>
#include <gmlib/include_mc.h>
#include <ila/include_all.h>
#include <modapi/addons/AddonsLoader.h>
#include <modapi/recipe/CustomRecipeRegistry.h>
#include <modapi/item/CustomItemRegistry.h>
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
#define LIB_VERSION_MINOR    0
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