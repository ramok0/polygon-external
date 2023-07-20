#pragma once
#include <menu_structures.h>

namespace data {
	inline bool menu_open;
	inline void* gameWindow;
	inline void* myWindow;
	inline int Width;
	inline int Height;
	inline double DeltaTime;
	inline long long LastFrameTimeStamp;
	inline unsigned long pid;
	inline void* driver_handle;
	inline unsigned long long base_address;
	inline float ScreenCenterX;
	inline float ScreenCenterY;
	inline WINDOW_TABS current_tab;
	inline float cache_per_second;
	inline float world_to_meters;
	inline bool should_self_destruct;
}


