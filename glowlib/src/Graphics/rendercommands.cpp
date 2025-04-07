#include "GlowEngine/Graphics/rendercommands.h"
#include "GlowEngine/engine.h"
#include "GlowEngine/log.h"

#include "GlowEngine/Graphics/mesh.h"
#include "GlowEngine/Graphics/shader.h"
#include "GlowEngine/Graphics/framebuffer.h"

#include "glad/glad.h"

namespace Glow
{
	void RenderMesh::Execute()
	{
		std::shared_ptr<Mesh> mesh = mMesh.lock();
		std::shared_ptr<Shader> shader = mShader.lock();
		if (mesh && shader) 
		{
			mesh->Bind();
			shader->Bind();

			if (mesh->GetElementCount() > 0)
			{
				glDrawElements(GL_TRIANGLES, mesh->GetElementCount(), GL_UNSIGNED_INT, 0);
			}
			else
			{
				glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->GetVertexCount());
			}

			shader->Unbind();
			mesh->Unbind();
		}
		else
		{
			GWE_WARN("Warning, Executing RenderMesh command with invalid pointers");
		}
	}

	
	void PushFrameBuffer::Execute()
	{
		std::shared_ptr<FrameBuffer> fb = mFrameBuffer.lock();
		if (!fb) { GWE_WARN("Warning, Executing PushFrameBuffer command with invalid pointers") }

		Engine::Instance().GetRenderer().PushFrameBuffer(fb);
	}

	void PopFrameBuffer::Execute()
	{
		Engine::Instance().GetRenderer().PopFrameBuffer();
	}

}