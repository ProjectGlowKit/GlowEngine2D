#pragma once
#include <tuple>

struct SDL_Window;
namespace Glow
{
	class Window
	{
	public:
		Window();
		~Window();

		bool Create();
		void Shutdown();
		void GetEvents();

		void RenderBegin();
		void RenderEnd();

		inline SDL_Window* GetSDLWindow() { return mWindow; }
		void GetSize(int& width, int& height);
	private:
		SDL_Window* mWindow;
		//SDL_GLContext mGLContext;
		void* mGLContext;
	};
}