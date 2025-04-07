#include "GlowEngine/Game/GameObject.h"
#include "GlowEngine/engine.h"

#include "thirdparty/glm/gtc/matrix_transform.hpp"

namespace Glow
{
	void GameObject::Render()
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, { mPos, 0.0f });
		model = glm::scale(model, { mSize, 0.0f });
		mShader->SetUniformMat4("model", model);
		Engine::Instance().GetRenderer().Submit(GWE_SUBMIT_RC(RenderMesh, mMesh, mShader));
	}
}