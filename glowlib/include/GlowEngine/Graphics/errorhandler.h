#pragma once
namespace Glow
{
	void GetGLErrors();
}

#ifdef GWE_CONFIG_DEBUG
	#define GWE_GET_GL_ERRORS Glow::GetGLErrors();
#else
	#define GWE_GET_GL_ERRORS void(0);
#endif