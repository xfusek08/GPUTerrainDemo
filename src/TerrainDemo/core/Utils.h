
#pragma once

#include <TerrainDemo/core/Log.h>
#include <sstream>

#define STREAM_TO_STR(S) static_cast<std::ostringstream&>(ostringstream() << S).str()

#define TD_LOG_ERROR(...)   TerrainDemo::core::Log::getLogger()->writeError(STREAM_TO_STR(__VA_ARGS__))
#define TD_LOG_WARNING(...) TerrainDemo::core::Log::getLogger()->writeWarning(STREAM_TO_STR(__VA_ARGS__))
#define TD_LOG_INFO(...)   TerrainDemo::core::Log::getLogger()->writeInfo(STREAM_TO_STR(__VA_ARGS__))

#ifdef TD_DEBUG
#define TD_LOG_DEBUG(...)   TerrainDemo::core::Log::getLogger()->writeDebug(STREAM_TO_STR(__VA_ARGS__))
#else
#define TD_LOG_DEBUG(...)
#endif

#ifdef TD_ENABLE_ASSERTS
#define TD_ASSERT(x, ...) { if(!(x)) { TD_LOG_ERROR(STREAM_TO_STR("Assertion Failed: " << __VA_ARGS__)); __debugbreak(); } }
#else
#define TD_ASSERT(x, ...)
#endif
