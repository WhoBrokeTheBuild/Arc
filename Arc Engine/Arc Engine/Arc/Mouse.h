#pragma once

#ifndef __ARC_MOUSE_H__
#define __ARC_MOUSE_H__

#include <string>
#include <SDL/SDL.h>

using std::string;

namespace Arc
{
	// Enum of mouse buttons including the wheel up/down
	enum MouseButton
	{
		INVALID_MOUSE_BUTTON = -1,

		MOUSE_BUTTON_LEFT,
		MOUSE_BUTTON_MIDDLE,
		MOUSE_BUTTON_RIGHT,
		MOUSE_BUTTON_WHEEL_DOWN,
		MOUSE_BUTTON_WHEEL_UP,

		NUM_MOUSE_BUTTONS

	}; // enum MouseButton

	const string MOUSE_BUTTON_NAMES[NUM_MOUSE_BUTTONS] =
	{
		"Left Button",
		"Middle Button",
		"Right Button",
		"Wheel Down",
		"Wheel Up"
	};

} // namespace Arc

#endif // __ARC_MOUSE_H__
