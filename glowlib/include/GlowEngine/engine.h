#pragma once
#include "GlowEngine/app.h"
#include "GlowEngine/Core/window.h"
#include "GlowEngine/Managers/logger.h"
#include "GlowEngine/Managers/renderer.h"

namespace Glow
{
    class App;
    class Engine
    {
    public:
        //Functions
        static Engine& Instance();
        ~Engine(){}

        void Run(App* app);
        inline void Quit() { mIsRunning = false; }

        inline App& GetApp() { return *mApp; }
        inline Window& GetWindow() { return mWindow; }

        //Public managers
        inline Renderer& GetRenderer() { return mRenderer; }
    private:
        //Private Functions
        bool Init();
        void Shutdown();
        void Update();
        void Render();
    private:
        App* mApp;

        Engine();
        static Engine* mEngine;

        Window mWindow;

        //Managers
        Logger mLogger;
        Renderer mRenderer;

        //Variables
        bool mIsRunning;
        bool mIsInitialized;
    };
}
