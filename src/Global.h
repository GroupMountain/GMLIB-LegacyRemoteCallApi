#pragma once
#include <RemoteCallAPI.h>
#include <include_all.h>

#define PLUGIN_NAME "GMLIB-LRCA"

extern ll::Logger logger;
extern bool       isServerStarted;

extern void Export_Legacy_GMLib_ModAPI();
extern void Export_Legacy_GMLib_ServerAPI();
extern void Export_Compatibility_API();