#pragma once

#include "GlowEngine/Core/window.h"

namespace Glow
{
	class App
	{
	public:
		App() {}
		~App() {}

		virtual void Init() {}
		virtual void Shutdown() {}

		virtual WindowProperties SetWindowProperties() { return WindowProperties(); }

		virtual void Update() {}
		virtual void Render() {}
		virtual void RenderImGui() {}
	private:
	};
}