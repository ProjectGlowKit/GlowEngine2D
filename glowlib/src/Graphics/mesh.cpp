#include "GlowEngine/Graphics/mesh.h"

#include "glad/glad.h"

namespace Glow
{
	Mesh::Mesh(float* vertexArray, uint32_t vertexCount, uint32_t dimensions)
		: mVertexCount(vertexCount), mEBO(0), mElementCount(0)
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

	Mesh::Mesh(float* vertexArray, uint32_t vertexCount, uint32_t dimensions, uint32_t* elementArray, uint32_t elementCount)
		: Mesh(vertexArray, vertexCount, dimensions)
	{
		mElementCount = elementCount;
		glBindVertexArray(mVAO);

		glGenBuffers(1, &mEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount * sizeof(uint32_t), elementArray, GL_STATIC_DRAW);

		glBindVertexArray(0);
	}

	Mesh::~Mesh()
	{
		glDeleteBuffers(1, &mPositionVBO); 
		if (mEBO != 0)
		{
			glDeleteBuffers(1, &mEBO);
		}
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