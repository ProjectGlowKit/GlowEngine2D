#pragma once

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
	private:
		SDL_Window* mWindow;
		//SDL_GLContext mGLContext;
		void* mGLContext;
	};
}