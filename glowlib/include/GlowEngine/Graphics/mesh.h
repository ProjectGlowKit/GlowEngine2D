#pragma once

#include <cstdint>

namespace Glow
{
	class Mesh
	{
	public:
		Mesh(float* vertexArray, uint64_t vertexCount, uint64_t dimensions);
		~Mesh();

		void Bind();
		void Unbind();

		inline uint32_t GetVertexCount() const { return mVertexCount; }
	private:
		uint32_t mVertexCount;
		uint32_t mVAO;

		uint32_t mPositionVBO;
	};
}