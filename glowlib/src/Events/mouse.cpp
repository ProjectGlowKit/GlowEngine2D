#include "GlowEngine/Events/mouse.h"
#include "GlowEngine/log.h"

#include <algorithm>

#include "SDL3/SDL_mouse.h"

namespace Glow
{
    glm::ivec2 Mouse::mPos(0, 0);
    glm::ivec2 Mouse::mPrevPos(0, 0);

    std::array<bool, Mouse::ButtonCount> Mouse::buttons = { false };
	std::array<bool, Mouse::ButtonCount> Mouse::buttonsDown = { false };
	std::array<bool, Mouse::ButtonCount> Mouse::buttonsUp = { false };

    void Mouse::Update() 
    {
        std::fill(buttonsDown.begin(), buttonsDown.end(), false);
        std::fill(buttonsUp.begin(), buttonsUp.end(), false);

        mPrevPos = mPos;
        
        float x, y;
        Uint32 state = SDL_GetMouseState(&x, &y);
        mPos.x = static_cast<int>(x);
        mPos.y = static_cast<int>(y);

        for (int i = 0; i < ButtonCount; i++)
        {
            bool wasDown = buttons[i];

            Uint32 buttonMask = 0;
            switch (i) 
            {
            case 0: buttonMask = SDL_BUTTON_LMASK; break;
            case 1: buttonMask = SDL_BUTTON_MMASK; break;
            case 2: buttonMask = SDL_BUTTON_RMASK; break;
            case 3: buttonMask = SDL_BUTTON_X1MASK; break;
            case 4: buttonMask = SDL_BUTTON_X2MASK; break;
            default: GWE_WARN("Invalid mouse button index") break;
            };
            buttons[i] = (state & buttonMask);
            bool isDown = buttons[i];

            if (wasDown && !isDown) { buttonsUp[i] = true; }
            else if(!wasDown && isDown) { buttonsDown[i] = true; }
        }
    }

    bool Mouse::Button(int button) 
    {
        if (button < 1 || button > ButtonCount) return false;
        return buttons[button - 1];
    }

    bool Mouse::ButtonDown(int button) 
    {
        if (button < 1 || button > ButtonCount) return false;
        return buttonsDown[button - 1];
    }

    bool Mouse::ButtonUp(int button) 
    {
        if (button < 1 || button > ButtonCount) return false;
        return buttonsUp[button - 1];
    }
}