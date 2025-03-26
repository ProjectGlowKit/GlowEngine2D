#include "GlowEngine/engine.h"
#include "GlowEngine/log.h"

#include "GlowEngine/Graphics/mesh.h"
#include "GlowEngine/Graphics/shader.h"

#include "GlowEngine/Events/mouse.h"
#include "GlowEngine/Events/keyboard.h"

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
                 0.5f,  0.5f, 0.0f,
                 0.5f, -0.5f, 0.0f,
                -0.5f, -0.5f, 0.0f,
                -0.5f,  0.5f, 0.0f
            };

            uint32_t indices[]
            {
                0, 3, 1,
                1, 3, 2
            };


            std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(&vertices[0], 4, 3, &indices[0], 6);

            //Test Shader
            const char* vertexShader = R"(
                #version 460 core
                layout (location = 0) in vec3 position;

                out vec3 vpos;
                uniform vec2 offset;
                void main()
                {
                    vpos = position + vec3(offset, 0);
                    gl_Position = vec4(position, 1.0);
                }
            )";

            const char* fragmentShader = R"(
                #version 460 core
                out vec4 outColor;
                in vec3 vpos;

                uniform vec3 color;
                void main()
                {
                    outColor = vec4(vpos, 1.0);
                }
            )";

            std::shared_ptr<Shader> shader = std::make_shared<Shader>(vertexShader, fragmentShader);

            shader->SetUniformFloat3("color", 1.0, 0, 0);

            mRenderer.SetClearColor(1.0, 1.0, 1.0, 1.0);
            mRenderer.SetWireFrameMode(false);
            while(mIsRunning)
            {
                mWindow.GetEvents();
                Mouse::Update();
                Keyboard::Update();

                int windowW, windowH;
                GetWindow().GetSize(windowW, windowH);

                //float xNorm = (float)Mouse::X() / (float)windowW;
                //float yNorm = (float)(windowH - Mouse::Y()) / (float)windowH;
                float xNorm = (float)(Mouse::DX()) / 25.0f;
                float yNorm = (float)(Mouse::DY()) / 25.0f;

                shader->SetUniformFloat2("offset", xNorm, yNorm);

                //Debug
                //GWE_TRACE("width: {} | height: {}", windowW, windowH);
                /*GWE_TRACE("Mouse: x{} | y{}", 
                    Mouse::X(), Mouse::Y())*/
                /*GWE_TRACE("Mouse: {} | {} | {} | {} | {}",
                    Mouse::Button(GWE_EVENT_MOUSE_LEFT),
                    Mouse::Button(GWE_EVENT_MOUSE_MIDDLE),
                    Mouse::Button(GWE_EVENT_MOUSE_RIGHT),
                    Mouse::Button(GWE_EVENT_MOUSE_X1),
                    Mouse::Button(GWE_EVENT_MOUSE_X2))*/
                /*GWE_TRACE("Keyboard: W:{} | S:{} | A:{} | D:{}",
                    Keyboard::Key(GWE_EVENT_KEY_W),
                    Keyboard::Key(GWE_EVENT_KEY_S),
                    Keyboard::Key(GWE_EVENT_KEY_A),
                    Keyboard::Key(GWE_EVENT_KEY_D))*/
                mWindow.RenderBegin();

                auto command = std::make_unique<RenderMesh>(mesh, shader);
                mRenderer.Submit(std::move(command));
                mRenderer.Flush();

                mWindow.RenderEnd();
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
            mLogger.Init();
            if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK) < 0)
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

            //Manager initialization
            GWE_INFO("Initializing managers...")
            mRenderer.Init();
            GWE_INFO("- Initialized Renderer")

            mIsInitialized = true;
            mIsRunning = true;

            GWE_INFO("Initialized GlowEngine!");
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