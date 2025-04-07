//Engine
#include "GlowEngine/engine.h"
#include "GlowEngine/app.h"
#include "GlowEngine/log.h"

#include "SDL3/SDL.h"

#include <iostream>

namespace Glow
{
    Engine* Engine::mEngine = nullptr;
    Engine::Engine()
        : mIsRunning(false), mIsInitialized(false), mApp(nullptr)
    {
    }

    Engine& Engine::Instance()
    {
        if (!mEngine)
        {
            mEngine = new Engine();
        }
        return *mEngine;
    }

    void Engine::Run(App* app)
    {
        mLogger.Init();
        GWE_ASSERT(app == nullptr, "Engine already has an App assigned")
        if (mApp) { return; }

        mApp = app;
        if (Init())
        {
            while(mIsRunning)
            {
                Update();
                Render();
            }
        }
        Shutdown();
    }

    //Private
    bool Engine::Init()
    {
        GWE_ASSERT(mIsInitialized, "Cannot initialize multiple times")
        if (!mIsInitialized)
        {
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK) < 0)
            {
                GWE_ERROR("Error initializing SDL3: {}", SDL_GetError())
                    Shutdown();
                return false;
            }
            GWE_INFO("Initialized SDL3")
            WindowProperties props = mApp->SetWindowProperties();
            if (!mWindow.Create(props))
            {
                return false;
            }
            GWE_INFO("Created a SDL window")

            mIsInitialized = true;
            mIsRunning = true;

            //Manager initialization
            GWE_INFO("Initializing managers...")
            mRenderer.Init();
            GWE_INFO("- Initialized Renderer")

            //Init Client
            mApp->Init();

            GWE_INFO("Initialized GlowEngine!");
            return true;
        }
        return false;
    }

    void Engine::Shutdown()
    {
        GWE_WARN("Shutting GlowEngine...")
        mIsInitialized = false;
        mIsRunning = false;

        //Client shutdown
        mApp->Shutdown();

        //Managers shutdown
        mRenderer.Shutdown();
        mLogger.Shutdown();

        mWindow.Shutdown();
        SDL_Quit();
    }

    void Engine::Update()
    {
        mWindow.GetEvents();
        mApp->Update();
    }

    void Engine::Render()
    {
        mWindow.RenderBegin();
        mApp->Render();
        mWindow.RenderEnd();
    }
}