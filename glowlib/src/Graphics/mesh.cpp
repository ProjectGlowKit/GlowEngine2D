#include "GlowEngine/Graphics/mesh.h"

#include "glad/glad.h"

namespace Glow
{
	Mesh::Mesh(float* vertexArray, uint64_t vertexCount, uint64_t dimensions)
		: mVertexCount(vertexCount)
	{
		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);

		glGenBuffers(1, &mPositionVBO);
		glBindBuffer(GL_ARRAY_BUFFER, mPositionVBO);
		glBufferData(GL_ARRAY_BUFFER, vertexCount * dimensions * sizeof(float), vertexArray, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, 0, 0);
		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &mPositionVBO);
		glDeleteVertexArrays(1, &mVAO);
	}

	void Mesh::Bind()
	{
		glBindVertexArray(mVAO);
		glEnableVertexAttribArray(0);
	}

	void Mesh::Unbind()
	{
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);
	}
}