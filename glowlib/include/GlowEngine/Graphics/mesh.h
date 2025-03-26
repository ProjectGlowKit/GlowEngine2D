#pragma once

#include <cstdint>

namespace Glow
{
	class Mesh
	{
	public:
		Mesh(float* vertexArray, uint32_t vertexCount, uint32_t dimensions);
		Mesh(float* vertexArray, uint32_t vertexCount, uint32_t dimensions, uint32_t* elementArray, uint32_t elementCount);
		~Mesh();

		void Bind();
		void Unbind();

		inline uint32_t GetVertexCount() const { return mVertexCount; }
		inline uint32_t GetElementCount() const { return mElementCount; }
	private:
		uint32_t mVertexCount, mElementCount;
		uint32_t mVAO, mEBO;
		uint32_t mPositionVBO;
	};
}