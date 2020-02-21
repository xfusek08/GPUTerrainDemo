
#pragma once

#include <GeoPlanetDemo/core/Log.h>
#include <sstream>

#define STREAM_TO_STR(S) (std::ostringstream() << S).str()

#define GPD_LOG_ERROR(...)  gpd::core::Log::getLogger()->writeError(STREAM_TO_STR(__VA_ARGS__))
#define GPD_LOG_WARNING(...) gpd::core::Log::getLogger()->writeWarning(STREAM_TO_STR(__VA_ARGS__))
#define GPD_LOG_INFO(...)  gpd::core::Log::getLogger()->writeInfo(STREAM_TO_STR(__VA_ARGS__))

#ifdef GPD_DEBUG
#define GPD_LOG_DEBUG(...)  gpd::core::Log::getLogger()->writeDebug(STREAM_TO_STR(__VA_ARGS__))
#else
#define GPD_LOG_DEBUG(...)
#endif

#ifdef GPD_ENABLE_ASSERTS
#define GPD_ASSERT(x, ...) { if(!(x)) { GPD_LOG_ERROR("Assertion Failed: " << __VA_ARGS__); __debugbreak(); } }
#else
#define GPD_ASSERT(x, ...)
#endif
