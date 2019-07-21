
#pragma once

#include <sstream>

#include <TerrainDemo/core/Log.h>

#define STREAM_TO_STR(S) static_cast<std::ostringstream&>(ostringstream() << S).str()

#ifdef TD_ENABLE_ASSERTS
  #define TD_ASSERT(x, ...) { if(!(x)) { TD_LOG_ERROR(STREAM_TO_STR("Assertion Failed: " << __VA_ARGS__)); __debugbreak(); } }
#else
  #define TD_ASSERT(x, ...)
#endif
