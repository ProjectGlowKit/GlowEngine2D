#include "GlowEngine/Graphics/errorhandler.h"
#include "GlowEngine/log.h"

#include "glad/glad.h"

namespace Glow
{
	void GetGLErrors()
	{
		GLenum error = glGetError();
		while (error != GL_NO_ERROR)
		{
			std::string errormsg;
			switch (error)
			{
			case GL_INVALID_OPERATION:				errormsg = "GL_INVALID_OPERATION"; break;
			case GL_INVALID_ENUM:					errormsg = "GL_INVALID_ENUM"; break;
			case GL_INVALID_VALUE:					errormsg = "GL_INVALID_VALUE"; break;
			case GL_OUT_OF_MEMORY:					errormsg = "GL_OUT_OF_MEMORY"; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:	errormsg = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
			default:								errormsg = std::to_string(error); break;
			}

			GWE_ERROR("OpenGL Error: {}", errormsg.c_str());
			GWE_ASSERT(false, "OpenGL Error");
			error = glGetError();
		}
	}
}