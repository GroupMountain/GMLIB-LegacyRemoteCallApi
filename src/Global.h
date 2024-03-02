#pragma once
#include <include_all.h>

#include <RemoteCallAPI.h>

#define PLUGIN_NAME "GMLIB-LRCA"
#define LIB_VERSION SemVersion(0, 9, 1, "", "")

extern ll::Logger logger;

extern void Export_Legacy_GMLib_ModAPI();
extern void Export_Legacy_GMLib_ServerAPI();
extern void Export_Compatibility_API();
extern void ExportPAPI();