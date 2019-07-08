
#pragma once

#include <TerrainDemo/core/Log.h>
#include <sstream>

#define STREAM_TO_STR(S) static_cast<std::ostringstream&>(ostringstream() << S).str()

#ifdef GPTR_ENABLE_ASSERTS
  #define GPTR_ASSERT(x, ...) { if(!(x)) { GPTR_LOG_ERROR(STREAM_TO_STR("Assertion Failed: " << __VA_ARGS__)); __debugbreak(); } }
#else
  #define GPTR_ASSERT(x, ...)
#endif
