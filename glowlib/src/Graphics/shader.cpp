#include "GlowEngine/Graphics/shader.h"
#include "GlowEngine/log.h"

#include "glad/glad.h"

#include "thirdparty/glm/gtc/type_ptr.hpp"

namespace Glow
{
	Shader::Shader(const std::string vertex, const std::string fragment)
	{
		mID = glCreateProgram(); 

		int result = GL_FALSE; 
		char error[512];

		uint32_t vertexShaderID = glCreateShader(GL_VERTEX_SHADER); 
		const GLchar* glSource = vertex.c_str();
		glShaderSource(vertexShaderID, 1, &glSource, NULL); 
		glCompileShader(vertexShaderID); 
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &result); 

		if(result != GL_TRUE)
		{
			glGetShaderInfoLog(vertexShaderID, sizeof(error), NULL, error); 
			GWE_ERROR("Vertex Shader compilation error: {}", error); 
		}
		else
		{
			glAttachShader(mID, vertexShaderID); 
		}

		uint32_t fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER); 
		glSource = fragment.c_str();
		glShaderSource(fragmentShaderID, 1, &glSource, NULL); 
		glCompileShader(fragmentShaderID); 
		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &result); 

		if (result != GL_TRUE)
		{
			glGetShaderInfoLog(fragmentShaderID, sizeof(error), NULL, error); 
			GWE_ERROR("Fragment Shader compilation error: {}", error); 
		}
		else
		{
			glAttachShader(mID, fragmentShaderID); 
		}

		GWE_ASSERT(result == GL_FALSE, "Error compiling shader"); 

		if (result == GL_TRUE)
		{
			glLinkProgram(mID); 
			glValidateProgram(mID); 
			glGetProgramiv(mID, GL_LINK_STATUS, &result); 
			if (result != GL_TRUE)
			{
				glGetProgramInfoLog(mID, sizeof(error), NULL, error); 
				GWE_ERROR("Error linking shader: {}", error); 
				glDeleteProgram(mID); 
				mID = -1;
			}
		}

		glDeleteShader(vertexShaderID); 
		glDeleteShader(fragmentShaderID); 
	}

	Shader::~Shader()
	{
		glUseProgram(0); 
		glDeleteProgram(mID); 
	}

	void Shader::Bind()
	{
		glUseProgram(mID); 
	}

	void Shader::Unbind()
	{
		glUseProgram(0); 
	}

	void Shader::SetUniformInt(const std::string name, int val)
	{
		glUseProgram(mID); 
		glUniform1i(static_cast<GLint>(GetUniformLocation(name)), val); 
	}
	void Shader::SetUniformFloat(const std::string name, float val)
	{
		glUseProgram(mID); 
		glUniform1f(GetUniformLocation(name), val); 
	}
	void Shader::SetUniformFloat2(const std::string name, float val1, float val2)
	{
		glUseProgram(mID); 
		glUniform2f(GetUniformLocation(name), val1, val2); 
	}
	void Shader::SetUniformFloat2(const std::string name, const glm::vec2 vec)
	{
		glUseProgram(mID);
		glUniform2f(GetUniformLocation(name), vec.x, vec.y);
	}
	void Shader::SetUniformFloat3(const std::string name, float val1, float val2, float val3)
	{
		glUseProgram(mID); 
		glUniform3f(GetUniformLocation(name), val1, val2, val3); 
	}
	void Shader::SetUniformFloat3(const std::string name, const glm::vec3 vec)
	{
		glUseProgram(mID);
		glUniform3f(GetUniformLocation(name), vec.x, vec.y, vec.z);
	}
	void Shader::SetUniformFloat4(const std::string name, float val1, float val2, float val3, float val4)
	{
		glUseProgram(mID); 
		glUniform4f(GetUniformLocation(name), val1, val2, val3, val4); 
	}
	void Shader::SetUniformFloat4(const std::string name, const glm::vec4 vec)
	{
		glUseProgram(mID);
		glUniform4f(GetUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
	}

	void Shader::SetUniformMat3(const std::string name, const glm::mat3 mat)
	{
		glUseProgram(mID);
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
	}
	void Shader::SetUniformMat4(const std::string name, const glm::mat4 mat)
	{
		glUseProgram(mID);
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
	}

	//Private
	int Shader::GetUniformLocation(const std::string name)
	{
		auto item = mUniformLocations.find(name);
		if (item == mUniformLocations.end())
		{
			mUniformLocations[name] = glGetUniformLocation(mID, name.c_str()); 
		}

		return mUniformLocations[name];
	}
}