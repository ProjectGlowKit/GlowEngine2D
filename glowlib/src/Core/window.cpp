#include "GlowEngine/Core/window.h"
#include "GlowEngine/engine.h"
#include "GlowEngine/app.h"
#include "GlowEngine/Graphics/framebuffer.h"

//Events
#include "GlowEngine/Events/mouse.h"
#include "GlowEngine/Events/keyboard.h"

#include "GlowEngine/log.h"

#include "SDL3/SDL.h"
#include "glad/glad.h"
#include "thirdparty/ImGui/imgui.h"

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

	bool Window::Create(const WindowProperties& props)
	{
		mWindow = SDL_CreateWindow(props.title.c_str(), props.size.x, props.size.y, SDL_WINDOW_OPENGL | ConvertSDLFlags(props));
		if (!mWindow) { GWE_FATAL("Error creating SDL window: {}", SDL_GetError()); return false; }
	#ifdef GWE_PLATFORM_MACOS
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG)
	#endif 
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		SDL_SetWindowMinimumSize(mWindow, props.sizeMin.x, props.sizeMin.y);

		mGLContext = SDL_GL_CreateContext(mWindow);
		if (mGLContext == nullptr) { GWE_ERROR("Error creating OpenGL Context: {}", SDL_GetError()); return false; }

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) { GWE_ERROR("Failed to initialize OpenGL loader!"); return false; }

		mFrameBuffer = std::make_shared<FrameBuffer>(props.size.x, props.size.y);
		mFrameBuffer->SetClearColor(props.clearColor);

		mImGuiWindow.Create(props.ImGuiProps);
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

			if (!mImGuiWindow.DoesCaptureMouse()) 
			{
				Mouse::Update();
			}
			if (!mImGuiWindow.DoesCaptureKeyboard()) 
			{
				Keyboard::Update();
			}
			mImGuiWindow.HandleSDLEvents(e);
		}
	}

	void Window::RenderBegin()
	{
		auto& renderer = Engine::Instance().GetRenderer();
		renderer.Clear();
		renderer.Submit(GWE_SUBMIT_RC(PushFrameBuffer, mFrameBuffer));
	}

	void Window::RenderEnd()
	{
		auto& renderer = Engine::Instance().GetRenderer();
		renderer.Submit(GWE_SUBMIT_RC(PopFrameBuffer));
		renderer.Flush();

		mImGuiWindow.RenderBegin();
		Engine::Instance().GetApp().RenderImGui();
		mImGuiWindow.RenderEnd();

		SDL_GL_SwapWindow(mWindow);
	}

	glm::ivec2 Window::GetSize()
	{
		int w, h;
		SDL_GetWindowSize(mWindow, &w, &h);
		return glm::ivec2(w, h);
	}

	uint64_t Window::ConvertSDLFlags(const WindowProperties& props)
	{
		uint64_t sdlFlags = 0;

		if (props.HasFlag(WindowFlags::Fullscreen)) sdlFlags |= SDL_WINDOW_FULLSCREEN;
		if (props.HasFlag(WindowFlags::OpenGL)) sdlFlags |= SDL_WINDOW_OPENGL;
		if (props.HasFlag(WindowFlags::Occluded)) sdlFlags |= SDL_WINDOW_OCCLUDED;
		if (props.HasFlag(WindowFlags::Hidden)) sdlFlags |= SDL_WINDOW_HIDDEN;
		if (props.HasFlag(WindowFlags::Borderless)) sdlFlags |= SDL_WINDOW_BORDERLESS;
		if (props.HasFlag(WindowFlags::Resizable)) sdlFlags |= SDL_WINDOW_RESIZABLE;
		if (props.HasFlag(WindowFlags::Minimized)) sdlFlags |= SDL_WINDOW_MINIMIZED;
		if (props.HasFlag(WindowFlags::Maximized)) sdlFlags |= SDL_WINDOW_MAXIMIZED;
		if (props.HasFlag(WindowFlags::MouseGrabbed)) sdlFlags |= SDL_WINDOW_MOUSE_GRABBED;
		if (props.HasFlag(WindowFlags::InputFocus)) sdlFlags |= SDL_WINDOW_INPUT_FOCUS;
		if (props.HasFlag(WindowFlags::MouseFocus)) sdlFlags |= SDL_WINDOW_MOUSE_FOCUS;
		if (props.HasFlag(WindowFlags::External)) sdlFlags |= SDL_WINDOW_EXTERNAL;
		if (props.HasFlag(WindowFlags::Modal)) sdlFlags |= SDL_WINDOW_MODAL;
		if (props.HasFlag(WindowFlags::HighPixelDensity)) sdlFlags |= SDL_WINDOW_HIGH_PIXEL_DENSITY;
		if (props.HasFlag(WindowFlags::MouseCapture)) sdlFlags |= SDL_WINDOW_MOUSE_CAPTURE;
		if (props.HasFlag(WindowFlags::MouseRelativeMode)) sdlFlags |= SDL_WINDOW_MOUSE_RELATIVE_MODE;
		if (props.HasFlag(WindowFlags::AlwaysOnTop)) sdlFlags |= SDL_WINDOW_ALWAYS_ON_TOP;
		if (props.HasFlag(WindowFlags::Utility)) sdlFlags |= SDL_WINDOW_UTILITY;
		if (props.HasFlag(WindowFlags::Tooltip)) sdlFlags |= SDL_WINDOW_TOOLTIP;
		if (props.HasFlag(WindowFlags::PopupMenu)) sdlFlags |= SDL_WINDOW_POPUP_MENU;
		if (props.HasFlag(WindowFlags::KeyboardGrabbed)) sdlFlags |= SDL_WINDOW_KEYBOARD_GRABBED;
		if (props.HasFlag(WindowFlags::Vulkan)) sdlFlags |= SDL_WINDOW_VULKAN;
		if (props.HasFlag(WindowFlags::Metal)) sdlFlags |= SDL_WINDOW_METAL;
		if (props.HasFlag(WindowFlags::Transparent)) sdlFlags |= SDL_WINDOW_TRANSPARENT;
		if (props.HasFlag(WindowFlags::NotFocusable)) sdlFlags |= SDL_WINDOW_NOT_FOCUSABLE;

		return sdlFlags;
	}
}