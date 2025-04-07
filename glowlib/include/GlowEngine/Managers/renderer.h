#pragma once
#include "GlowEngine/Graphics/rendercommands.h"

#include "thirdparty/glm/glm.hpp"

#include <stack>
#include <queue>
#include <memory>

#define GWE_SUBMIT_RC(type, ...) std::move(std::make_unique<type>(__VA_ARGS__))

namespace Glow
{
	class Renderer
	{
		friend class PushFrameBuffer;
		friend class PopFrameBuffer;
	public:
		Renderer(){}
		~Renderer(){}

		void Init();
		void Shutdown();

		void Clear();
		void SetViewport(glm::vec4 xywh);
		void SetClearColor(glm::vec4 rgba);
		void SetWireFrameMode(bool enabled);

		void Submit(std::unique_ptr<RenderCommand> command);
		void Flush();

	private:
		void PushFrameBuffer(std::shared_ptr<FrameBuffer> framebuffer);
		void PopFrameBuffer();
	private:
		std::queue<std::unique_ptr<RenderCommand>> mRenderCommands;
		std::stack<std::shared_ptr<FrameBuffer>> mFrameBuffers;
	};
}