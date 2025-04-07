#pragma once
#include "GlowEngine/Core/imguiwindow.h"
#include "GlowEngine/Graphics/framebuffer.h"

#include <tuple>
#include <string>
#include <memory>

#include "thirdparty/glm/glm.hpp"

struct SDL_Window;
namespace Glow
{
	enum WindowFlags : uint64_t
	{
		Fullscreen = 1ULL << 0,   // SDL_WINDOW_FULLSCREEN
		OpenGL = 1ULL << 1,   // SDL_WINDOW_OPENGL
		Occluded = 1ULL << 2,   // SDL_WINDOW_OCCLUDED
		Hidden = 1ULL << 3,   // SDL_WINDOW_HIDDEN
		Borderless = 1ULL << 4,   // SDL_WINDOW_BORDERLESS
		Resizable = 1ULL << 5,   // SDL_WINDOW_RESIZABLE
		Minimized = 1ULL << 6,   // SDL_WINDOW_MINIMIZED
		Maximized = 1ULL << 7,   // SDL_WINDOW_MAXIMIZED
		MouseGrabbed = 1ULL << 8,   // SDL_WINDOW_MOUSE_GRABBED
		InputFocus = 1ULL << 9,   // SDL_WINDOW_INPUT_FOCUS
		MouseFocus = 1ULL << 10,  // SDL_WINDOW_MOUSE_FOCUS
		External = 1ULL << 11,  // SDL_WINDOW_EXTERNAL
		Modal = 1ULL << 12,  // SDL_WINDOW_MODAL
		HighPixelDensity = 1ULL << 13,  // SDL_WINDOW_HIGH_PIXEL_DENSITY
		MouseCapture = 1ULL << 14,  // SDL_WINDOW_MOUSE_CAPTURE
		MouseRelativeMode = 1ULL << 15,  // SDL_WINDOW_MOUSE_RELATIVE_MODE
		AlwaysOnTop = 1ULL << 16,  // SDL_WINDOW_ALWAYS_ON_TOP
		Utility = 1ULL << 17,  // SDL_WINDOW_UTILITY
		Tooltip = 1ULL << 18,  // SDL_WINDOW_TOOLTIP
		PopupMenu = 1ULL << 19,  // SDL_WINDOW_POPUP_MENU
		KeyboardGrabbed = 1ULL << 20,  // SDL_WINDOW_KEYBOARD_GRABBED
		Vulkan = 1ULL << 28,  // SDL_WINDOW_VULKAN
		Metal = 1ULL << 29,  // SDL_WINDOW_METAL
		Transparent = 1ULL << 30,  // SDL_WINDOW_TRANSPARENT
		NotFocusable = 1ULL << 31   // SDL_WINDOW_NOT_FOCUSABLE
	};

	struct WindowProperties
	{
		std::string title;
		glm::ivec2 size;
		glm::ivec2 sizeMin;
		uint64_t flags;
		glm::fvec4 clearColor;
		ImGuiWindowProperties ImGuiProps;

		WindowProperties()
			: size(800, 600), sizeMin(200, 200), flags(0), clearColor(0.0f, 0.0f, 0.0f, 1.0f), ImGuiProps{} {
		}

		inline void SetFlag(WindowFlags flag) { flags |= flag; }
		inline bool HasFlag(WindowFlags flag) const { return (flags & flag) != 0; }
	};

	class Window
	{
	public:
		Window();
		~Window();

		bool Create(const WindowProperties& props);
		void Shutdown();
		void GetEvents();

		void RenderBegin();
		void RenderEnd();

		inline SDL_Window* GetSDLWindow() { return mWindow; }
		inline void* GetGLContext() { return mGLContext; }
		inline FrameBuffer* GetFrameBuffer() { return mFrameBuffer.get(); }
		glm::ivec2 GetSize();
	private:
		SDL_Window* mWindow;
		void* mGLContext;
		ImGuiWindow mImGuiWindow;
		std::shared_ptr<FrameBuffer> mFrameBuffer;
		
		uint64_t ConvertSDLFlags(const WindowProperties& props);
	};
}