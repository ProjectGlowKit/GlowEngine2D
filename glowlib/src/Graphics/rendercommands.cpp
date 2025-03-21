#include "GlowEngine/Graphics/rendercommands.h"
#include "GlowEngine/log.h"

#include "GlowEngine/Graphics/mesh.h"
#include "GlowEngine/Graphics/shader.h"

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

			glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->GetVertexCount());

			shader->Unbind();
			mesh->Unbind();
		}
		else
		{
			GWE_WARN("Warning, Executing RenderMesh command with invalid pointers");
		}
	}
}