#pragma once
#include <RemoteCallAPI.h>
#include <headers/include_all.h>

using namespace gmlib;
using namespace world;
using namespace mod;
using namespace tools;

#define PLUGIN_NAME fmt::format(fg(fmt::color::light_green), "GMLIB-LRCA")

#define LIB_VERSION_MAJOR 0
#define LIB_VERSION_MINOR 13
#define LIB_VERSION_PATCH 4

#define LIB_VERSION Version(LIB_VERSION_MAJOR, LIB_VERSION_MINOR, LIB_VERSION_PATCH)

extern ll::Logger logger;

extern void Export_Legacy_GMLib_ModAPI();
extern void Export_Legacy_GMLib_ServerAPI();
extern void Export_Compatibility_API();
extern void ExportPAPI();
extern void Export_Event_API();
extern void Export_Form_API();