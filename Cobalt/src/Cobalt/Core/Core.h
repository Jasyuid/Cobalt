#pragma once

#include "Logger.h"

// Enable asserts if in debug mode and enable breakpoints if on windows
#ifndef NDEBUG
	#if defined(CB_PLATFORM_WINDOWS)
		#define CB_DEBUGBREAK() __debugbreak()
	#endif
	#define CB_ENABLE_ASSERTS
#else
	#define CB_DEBUGBREAK()
#endif

// Assert functionality if needed
#ifdef CB_ENABLE_ASSERTS
	#define CB_ASSERT(x, m) { if(!(x)) { CB_ERROR("Assertion Failed: {0} ({1}:{2})", m, __FILE__, __LINE__); CB_DEBUGBREAK(); }}
	#define CB_CORE_ASSERT(x, m) { if(!(x)) { CB_CORE_ERROR("Assertion Failed: {0} ({1}:{2})", m, __FILE__, __LINE__); CB_DEBUGBREAK(); }}
#else
	#define CB_ASSERT(x, m)
	#define CB_CORE_ASSERT(x, m)
#endif

// Macro for changing specific bits
#define BIT(X) (1 << X)
