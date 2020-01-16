#pragma once

#include "d2dpch.h"

typedef unsigned int uint;

/* #undef D2D_PLATFORM_WINDOWS */
/* #undef D2D_BUILD_DLLS */

#ifdef D2D_PLATFORM_WINDOWS

	#ifdef D2D_BUILD_DLLS
		#define D2D_API __declspec(dllexport)
	#else
		#define D2D_API __declspec(dllimport)
	#endif

#else
	#define D2D_API

#endif

#define D2D_BIT(x) 1 << x

#define D2D_CHECK_EVENT_TYPE(event, type) if (event.GetEventType() == d2d::EventType::type)
#define D2D_CHECK_FULL_EVENT_TYPE(event, fullType) if (event.GetEventType() == fullType)
