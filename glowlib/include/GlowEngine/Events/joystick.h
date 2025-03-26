#pragma once

#include <vector>
#include <SDL3/SDL.h>

namespace Glow
{
	class Joystick
	{
	public:
		Joystick(int joystickIndex = 0);

		bool IsOpen() const;

		void Update();

		int GetButtonCount() const;
		int GetAxisCount() const;

		bool Button(int button) const;
		bool ButtonDown(int button) const;
		bool ButtonUp(int button) const;
		int Axis(int axis) const;
	private:

		struct Controller
		{
			SDL_Joystick* joystick = nullptr;

			std::vector<bool> buttons;
			std::vector<bool> buttonsDown;
			std::vector<bool> buttonsUp;

			std::vector<int> axes;
			std::vector<int> axesPrev;
		};
	};
}