#include "GlowEngine/Core/imguiwindow.h"

#include "GlowEngine/engine.h"
#include "GlowEngine/log.h"

#include "SDL3/SDL_events.h"

#include "thirdparty/ImGui/imgui.h"
#include "thirdparty/ImGui/imgui_impl_sdl3.h"
#include "thirdparty/ImGui/imgui_impl_opengl3.h"

#include "SDL3/SDL.h"
namespace Glow
{
	void ImGuiWindow::Create(const ImGuiWindowProperties& props)
	{
		IMGUI_CHECKVERSION();

		ImGui::CreateContext();

		ImGuiIO& io = ImGui::GetIO();
		io.ConfigWindowsMoveFromTitleBarOnly = props.moveFromTitleBar;
		if (props.isDockingEnabled) { io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; }
		if (props.isViewportEnabled) { io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; }

		auto& window = Engine::Instance().GetWindow();
		ImGui_ImplSDL3_InitForOpenGL(window.GetSDLWindow(), window.GetGLContext());
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void ImGuiWindow::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiWindow::HandleSDLEvents(SDL_Event& event)
	{
		ImGui_ImplSDL3_ProcessEvent(&event);
	}

	bool ImGuiWindow::DoesCaptureMouse()
	{
		return ImGui::GetIO().WantCaptureMouse;
	}

	bool ImGuiWindow::DoesCaptureKeyboard()
	{
		return ImGui::GetIO().WantCaptureKeyboard;
	}

	void ImGuiWindow::RenderBegin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiWindow::RenderEnd()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			auto& window = Engine::Instance().GetWindow();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(window.GetSDLWindow(), (SDL_GLContext)window.GetGLContext());
		}
	}
}