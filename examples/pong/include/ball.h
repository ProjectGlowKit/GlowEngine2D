#pragma once

#include "GlowEngine/Graphics/mesh.h"
#include "GlowEngine/Graphics/shader.h"

#include "GlowEngine/Game/GameObject.h"

#include <memory>

namespace Ball
{
	class Ball : public Glow::GameObject
	{
	public:
		Ball(std::shared_ptr<Glow::Mesh> mesh, std::shared_ptr<Glow::Shader> shader)
			:GameObject(mesh, shader), mVelocity(0.0f)
		{
		}

		inline void SetVelocity(const glm::vec2 velocity) { mVelocity = velocity; }
		inline glm::vec2 GetVelocity() { return mVelocity; }
		inline void IncrementVelocity(const glm::vec2 velocity) { mVelocity += velocity; }
		inline void VelocityFlipX() { mVelocity.x *= -1; }
		inline void VelocityFlipY() { mVelocity.y *= -1; }
	private:
		glm::vec2 mVelocity;
	};

	std::shared_ptr<Ball> CreateBall();
}