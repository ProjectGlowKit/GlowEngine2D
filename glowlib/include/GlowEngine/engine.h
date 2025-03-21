#pragma once
#include "GlowEngine/Core/window.h"
#include "GlowEngine/Managers/logger.h"
#include "GlowEngine/Managers/renderer.h"

namespace Glow
{
    class Engine
    {
    public:
        //Functions
        static Engine& Instance();
        void Run();
        inline void Quit() { mIsRunning = false; }

        //Public managers
        inline Renderer& GetRenderer() { return mRenderer; }
    private:
        static Engine* mEngine;
        Window mWindow;

        //Variables
        bool mIsRunning;
        bool mIsInitialized;

        //Functions
        Engine();
        ~Engine();

        bool Init();
        void Shutdown();

        //Private Managers
        Logger mLogger;
        Renderer mRenderer;
    };
}
