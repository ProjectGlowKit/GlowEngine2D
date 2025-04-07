#include "GlowEngine/Graphics/framebuffer.h"
#include "GlowEngine/log.h"

#include "glad/glad.h"

namespace Glow
{
	FrameBuffer::FrameBuffer(uint32_t width, uint32_t height)
		: mFBO(0), mTexID(0), mBufferID(0), mWidth(width), mHeight(height), mClearColor(0.0f, 0.0f, 0.0f, 0.0f)
	{
		glGenFramebuffers(1, &mFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

		//Create color texture
		glGenTextures(1, &mTexID);
		glBindTexture(GL_TEXTURE_2D, mTexID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexID, 0);

		//Create depth/stencil buffer
		glGenRenderbuffers(1, &mBufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, mBufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, mWidth, mHeight);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mBufferID);

		//Check status
		int32_t status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE){ GWE_ERROR("Error creating a frame buffer: {}", status) }

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &mFBO);
		mFBO = 0;
		mTexID = 0;
		mBufferID = 0;
	}
}