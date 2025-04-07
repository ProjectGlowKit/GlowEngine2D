#pragma once

#include <array>

#include "thirdparty/glm/glm.hpp"

namespace Glow
{
	class Mouse
	{
	public:
		static void Update();

		inline static glm::ivec2 pos() { return mPos; }
		inline static glm::ivec2 prevPos() { return mPrevPos; }
		inline static glm::ivec2 delta() { return mPos - mPrevPos; }

		static bool Button(int button);
		static bool ButtonDown(int button);
		static bool ButtonUp(int button);

	private:
		constexpr static const int ButtonCount = 5;

		static glm::ivec2 mPos;
		static glm::ivec2 mPrevPos;

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