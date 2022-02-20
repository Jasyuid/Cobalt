#pragma once

#include "KeyCodes.h"
#include "MouseButtonCodes.h"

namespace Cobalt
{
	class Input
	{
	public:
		static bool IsKeyPressed(unsigned int key);

		static bool IsMouseButtonPressed(unsigned int button);
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}