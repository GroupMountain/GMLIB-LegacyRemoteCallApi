#pragma once
#include <include_all.h>

#include <RemoteCallAPI.h>

using namespace GMLIB;
using namespace Server;
using namespace Mod;

#define PLUGIN_NAME fmt::format(fg(fmt::color::light_green), "GMLIB-LRCA")

#define LIB_VERSION_MAJOR 0
#define LIB_VERSION_MINOR 13
#define LIB_VERSION_PATCH 3

#define LIB_VERSION Version(LIB_VERSION_MAJOR, LIB_VERSION_MINOR, LIB_VERSION_PATCH)

extern ll::Logger logger;

extern void Export_Legacy_GMLib_ModAPI();
extern void Export_Legacy_GMLib_ServerAPI();
extern void Export_Compatibility_API();
extern void ExportPAPI();
extern void Export_Event_API();
extern void Export_BinaryStream_API();
extern void Export_Form_API();
