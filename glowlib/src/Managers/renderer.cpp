#include "GlowEngine/Managers/renderer.h"
#include "GlowEngine/log.h"

#include "glad/glad.h"

namespace Glow
{
	void Renderer::Init()
	{
		glEnable(GL_DEPTH_TEST); 
		glDepthFunc(GL_LEQUAL); 

		glEnable(GL_BLEND); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	}

	void Renderer::Shutdown()
	{
		while(mRenderCommands.size() > 0)
		{
			mRenderCommands.pop();
		}
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	}

	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		GWE_ASSERT(mRenderCommands.size() != 0, "Unflushed render commands");
		while (mRenderCommands.size() > 0)
		{
			mRenderCommands.pop();
		}
		glClearColor(r, g, b, a);
	}

	void Renderer::SetWireFrameMode(bool enabled)
	{
		if(enabled)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	void Renderer::Submit(std::unique_ptr<RenderCommand> command)
	{
		mRenderCommands.push(std::move(command));
	}

	void Renderer::Flush()
	{
		while(mRenderCommands.size() > 0)
		{
			auto command = std::move(mRenderCommands.front());
			mRenderCommands.pop();
			command->Execute();
		}
	}
}