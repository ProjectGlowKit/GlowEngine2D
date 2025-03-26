#include "GlowEngine/Events/keyboard.h"
#include "GlowEngine/log.h"

#include <algorithm>

#include "SDL3/SDL_keyboard.h"

namespace Glow
{
	std::array<bool, Keyboard::KeyCount> Keyboard::keys = { false };
	std::array<bool, Keyboard::KeyCount> Keyboard::keysDown = { false };
	std::array<bool, Keyboard::KeyCount> Keyboard::keysUp = { false };

	void Keyboard::Update()
	{
		std::fill(keysDown.begin(), keysDown.end(), false);
		std::fill(keysUp.begin(), keysUp.end(), false);

		const bool* state = SDL_GetKeyboardState(nullptr);
		for (int i = GWE_EVENT_KEY_FIRST; i < KeyCount; i++)
		{
			bool wasDown = keys[i];
			keys[i] = state[i];
			bool isDown = keys[i];

			if (wasDown && !isDown) { keysUp[i] = true; }
			else if (!wasDown && isDown) { keysDown[i] = true; }
		}
	}

	bool Keyboard::Key(int key)
	{
		if (key >= GWE_EVENT_KEY_FIRST && key < KeyCount)
		{
			return keys[key];
		}
		return false;
	}

	bool Keyboard::KeyDown(int key)
	{
		if (key >= GWE_EVENT_KEY_FIRST && key < KeyCount)
		{
			return keysDown[key];
		}
		return false;
	}

	bool Keyboard::KeyUp(int key)
	{
		if (key >= GWE_EVENT_KEY_FIRST && key < KeyCount)
		{
			return keysUp[key];
		}
		return false;
	}
}