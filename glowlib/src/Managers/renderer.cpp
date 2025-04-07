#include "GlowEngine/Managers/renderer.h"
#include "GlowEngine/engine.h"
#include "GlowEngine/Graphics/framebuffer.h"
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

	void Renderer::SetViewport(glm::vec4 xywh)
	{
		glViewport(xywh.x, xywh.y, xywh.z, xywh.w);
	}

	void Renderer::SetClearColor(glm::vec4 rgba)
	{
		GWE_ASSERT(mRenderCommands.size() != 0, "Unflushed render commands");
		while (mRenderCommands.size() > 0)
		{
			mRenderCommands.pop();
		}
		glClearColor(rgba.r, rgba.g, rgba.b, rgba.a);
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

	//Private
	void Renderer::PushFrameBuffer(std::shared_ptr<FrameBuffer> framebuffer)
	{
		mFrameBuffers.push(framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->GetFBO());
		uint32_t w, h;
		framebuffer->GetSize(w, h);
		SetViewport(glm::vec4(0, 0, w, h));

		glm::fvec4 clearColor = framebuffer->GetClearColor();
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::PopFrameBuffer()
	{
		GWE_ASSERT(!(mFrameBuffers.size() > 0), "Renderer::PopFrameBuffer - empty stack")
		if (mFrameBuffers.size() > 0)
		{
			mFrameBuffers.pop();
			if (mFrameBuffers.size() > 0)
			{
				auto nextFb = mFrameBuffers.top();
				glBindFramebuffer(GL_FRAMEBUFFER, nextFb->GetFBO());
				uint32_t w, h;
				nextFb->GetSize(w, h);
				SetViewport(glm::vec4(0, 0, w, h));
			}
			else
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				auto& window = Engine::Instance().GetWindow();
				glm::ivec2 size = window.GetSize();
				SetViewport(glm::vec4(0, 0, size.x, size.y));
			}
		}
	}
}