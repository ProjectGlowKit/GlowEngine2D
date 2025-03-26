#pragma once

#include <array>

namespace Glow
{
	class Mouse
	{
	public:
		static void Update();

		inline static int X() { return x; }
		inline static int Y() { return y; }
		inline static int prevX() { return xPrev; }
		inline static int prevY() { return yPrev; }
		inline static int DX() { return x - xPrev; }
		inline static int DY() { return y - yPrev; }

		static bool Button(int button);
		static bool ButtonDown(int button);
		static bool ButtonUp(int button);

	private:
		constexpr static const int ButtonCount = 5;

		static float x, y;
		static float xPrev, yPrev;

		static std::array<bool, ButtonCount> buttons;
		static std::array<bool, ButtonCount> buttonsDown;
		static std::array<bool, ButtonCount> buttonsUp;
	};
}

enum
{
	GWE_EVENT_MOUSE_LEFT = 1,
	GWE_EVENT_MOUSE_MIDDLE = 2,
	GWE_EVENT_MOUSE_RIGHT = 3,
	GWE_EVENT_MOUSE_X1 = 4,
	GWE_EVENT_MOUSE_X2 = 5
};