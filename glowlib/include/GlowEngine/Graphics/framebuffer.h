#pragma once
#include <cstdint>

#include "thirdparty/glm/glm.hpp"

namespace Glow
{
	class FrameBuffer
	{
	public:
		FrameBuffer(uint32_t width, uint32_t height);
		~FrameBuffer();

		inline uint32_t GetFBO() const { return mFBO; }
		inline uint32_t GetTexID() const { return mTexID; }
		inline uint32_t GetBufferID() const { return mBufferID; }
		inline void GetSize(uint32_t& width, uint32_t& height) { width = mWidth; height = mHeight; }
		inline void SetClearColor(glm::fvec4 clearColor) { mClearColor = clearColor; }
		inline glm::fvec4 GetClearColor() { return mClearColor; }
	private:
		uint32_t mFBO;
		uint32_t mTexID;
		uint32_t mBufferID;
		uint32_t mWidth, mHeight;
		glm::fvec4 mClearColor;
	};
}