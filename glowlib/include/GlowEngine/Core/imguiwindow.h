#pragma once

typedef union SDL_Event SDL_Event;
namespace Glow
{
	struct ImGuiWindowProperties
	{
		bool moveFromTitleBar = true;
		bool isDockingEnabled = false;
		bool isViewportEnabled = false;
		ImGuiWindowProperties(){}
	};

	class ImGuiWindow
	{
	public:
		ImGuiWindow(){}
		~ImGuiWindow(){}

		void Create(const ImGuiWindowProperties& props);
		void Shutdown();

		void HandleSDLEvents(SDL_Event& event);

		bool DoesCaptureMouse();
		bool DoesCaptureKeyboard();

		void RenderBegin();
		void RenderEnd();
	};
}