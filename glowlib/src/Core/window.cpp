#include "GlowEngine/Core/window.h"
#include "GlowEngine/engine.h"

//Events
#include "GlowEngine/Events/mouse.h"

#include "GlowEngine/log.h"

#include "SDL3/SDL.h"
#include "glad/glad.h"

namespace Glow
{
	Window::Window() : mWindow(nullptr) {}
	Window::~Window()
	{
		if (mWindow)
		{
			Shutdown();
		}
	}

	bool Window::Create()
	{
		mWindow = SDL_CreateWindow("GlowEngine", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (!mWindow) { GWE_FATAL("Error creating SDL window: {}", SDL_GetError()); return false; }
	#ifdef GWE_PLATFORM_MACOS
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG)
	#endif 
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		SDL_SetWindowMinimumSize(mWindow, 200, 200);

		mGLContext = SDL_GL_CreateContext(mWindow);
		if (mGLContext == nullptr) { GWE_ERROR("Error creating OpenGL Context: {}", SDL_GetError()); return false; }

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) { GWE_ERROR("Failed to initialize OpenGL loader!"); return false; }

		return true;
	}

	void Window::Shutdown()
	{
		SDL_DestroyWindow(mWindow);
		SDL_GL_DestroyContext(SDL_GLContext(mGLContext));
		mWindow = nullptr;
	}

	void Window::GetEvents()
	{
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_EVENT_QUIT:
				Engine::Instance().Quit();
				break;
			default:
				break;
			};
		}
	}

	void Window::RenderBegin()
	{
		Engine::Instance().GetRenderer().Clear();
	}

	void Window::RenderEnd()
	{
		SDL_GL_SwapWindow(mWindow);
	}

	void Window::GetSize(int& width, int& height)
	{
		SDL_GetWindowSize(mWindow, &width, &height);
	}
}