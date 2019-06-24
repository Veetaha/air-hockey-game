#pragma once

#include "TypeDefs.h"

struct Dimensions2D {
	int width;
	int height;

	SDL_Rect toSdlRectAt(const Vector2D& location) {
		return { 
			static_cast<int>(std::round(location.x())),
			static_cast<int>(std::round(location.y())), 
			width, 
			height 
		};
	}
};