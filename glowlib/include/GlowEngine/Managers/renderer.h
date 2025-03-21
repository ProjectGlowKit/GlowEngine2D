#pragma once
#include "GlowEngine/Graphics/rendercommands.h"

#include <queue>

namespace Glow
{
	class Renderer
	{
	public:
		Renderer(){}
		~Renderer(){}

		void Init();
		void Shutdown();

		void Clear();
		void SetClearColor(float r, float g, float b, float a);

		void Submit(std::unique_ptr<RenderCommand> command);
		void Flush();
	private:
		std::queue<std::unique_ptr<RenderCommand>> mRenderCommands;
	};
}