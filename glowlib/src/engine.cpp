#include "GlowEngine/engine.h"
#include "GlowEngine/log.h"

#include "GlowEngine/Graphics/mesh.h"
#include "GlowEngine/Graphics/shader.h"

#include "SDL3/SDL.h"

#include <iostream>

namespace Glow
{
    Engine* Engine::mEngine = nullptr;

    Engine& Engine::Instance()
    {
        if (!mEngine)
        {
            mEngine = new Engine();
        }
        return *mEngine;
    }

    void Engine::Run()
    {
        if (Init())
        {
            // Test mesh
            float vertices[]
            {
                -0.5f,   -0.5f,   0.0f,
                 0.0f,    0.5f,   0.0f,
                 0.5f,   -0.5f,   0.0f
            };
            std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(&vertices[0], 3, 3);

            //Test Shader
            const char* vertexShader = R"(
                #version 460 core
                layout (location = 0) in vec3 position;
                void main()
                {
                    gl_Position = vec4(position, 1.0);
                }
            )";

            const char* fragmentShader = R"(
                #version 460 core
                out vec4 outColor;
                void main()
                {
                    outColor = vec4(1.0);
                }
            )";

            std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexShader, fragmentShader);

            while(mIsRunning)
            {
                mWindow.GetEvents();

                mWindow.RenderBegin();

                auto command = std::make_unique<RenderMesh>(mesh, shader);
                mRenderer.Submit(std::move(command));
                mRenderer.Flush();

                mWindow.RenderEnd();
            }
            Shutdown();
        }
    }

    //Private
    bool Engine::Init()
    {
        GWE_ASSERT(mIsInitialized, "Cannot initialize multiple times")
        if (!mIsInitialized)
        {
            mLogger.Init();
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
            {
                GWE_ERROR("Error initializing SDL3: {}", SDL_GetError())
                    Shutdown();
                return false;
            }
            GWE_INFO("Initialized SDL3")
                if (!mWindow.Create())
                {
                    return false;
                }
            GWE_INFO("Created a SDL window")
            GWE_INFO("Initializing managers...")
            //Manager initialization
            mRenderer.Init();
            GWE_INFO("  Initialized Renderer")
            GWE_INFO("Initialized GlowEngine!");
            mIsInitialized = true;
            mIsRunning = true;
            return true;
        }
        return false;
    }

    Engine::Engine() 
        : mIsRunning(false), mIsInitialized(false)
    {
    }

    void Engine::Shutdown()
    {
        GWE_WARN("Shutting GlowEngine...")
        mIsInitialized = false;
        mIsRunning = false;

        //Managers shutdown
        mRenderer.Shutdown();
        mLogger.Shutdown();

        mWindow.Shutdown();
        SDL_Quit();
    }

    Engine::~Engine()
    {
        if (mIsRunning) { Shutdown(); }
    }
}