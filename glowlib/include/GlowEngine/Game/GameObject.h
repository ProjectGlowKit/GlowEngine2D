#pragma once
#include "GlowEngine/Graphics/mesh.h"
#include "GlowEngine/Graphics/shader.h"

#include "thirdparty/glm/glm.hpp"

#include <memory>

namespace Glow
{
	class GameObject
	{
	public:
		GameObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<Shader> shader)
			:mMesh(mesh), mShader(shader), mPos(0, 0), mSize(1, 1)
		{}

		inline void SetShader(const std::shared_ptr<Shader> shader) { mShader = shader; }
		inline void SetPos(const glm::vec2 pos) { mPos = pos; }
		inline void AddPos(const glm::vec2 pos) { mPos += pos; }
		inline void SetSize(const glm::vec2 size) { mSize = size; }
		inline void AddSize(const glm::vec2 size) { mSize += size; }

		inline std::shared_ptr<Mesh> GetMesh() { return mMesh; }
		inline std::shared_ptr<Shader> GetShader() { return mShader; }
		inline glm::vec2 GetPos() { return mPos; }
		inline glm::vec2 GetSize() { return mSize; }

		void Render();

	private:
		std::shared_ptr<Mesh> mMesh;
		std::shared_ptr<Shader> mShader;

		glm::vec2 mPos;
		glm::vec2 mSize;
	};
}