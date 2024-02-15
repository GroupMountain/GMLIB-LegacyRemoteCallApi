#pragma once
#include <include_all.h>
#include <RemoteCallAPI.h>

#define PLUGIN_NAME "GMLIB-LRCA"

extern ll::Logger logger;

extern void Export_Legacy_GMLib_ModAPI();
extern void Export_Legacy_GMLib_ServerAPI();
extern void Export_Compatibility_API();