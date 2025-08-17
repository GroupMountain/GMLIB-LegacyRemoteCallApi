#pragma once
// clang-format off
#pragma warning(push)
#pragma warning(disable : 4996)
#define GMLIB_GLOBAL_USING
#include <gmlib/GlobalUsing.h>
#include <gmlib/include_all.h>
#include <ila/include_all.h>
#include <RemoteCallAPI.h>
using namespace gmlib::mod;
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