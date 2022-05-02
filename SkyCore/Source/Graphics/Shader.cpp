#include "SkyCore.h"
#include "Shader.h"
#include "Utils/FileRead.h"

namespace sky
{

	static void CheckShaderCompilation(uint32_t shaderhandle);
	static void CheckProgramLinkage(uint32_t shaderhandle);

	Shader::Shader(const std::string& path)
		:m_Program(0)
	{

		std::vector<char> vertexShaderSource;
		sky::ReadFile(path + ".vert", vertexShaderSource);

		std::vector<char> fragShaderSource;
		sky::ReadFile(path + ".frag", fragShaderSource);

		uint32_t vs = glCreateShader(GL_VERTEX_SHADER);
		uint32_t fs = glCreateShader(GL_FRAGMENT_SHADER);


		char* vsSource = vertexShaderSource.data();
		char* fsSource = fragShaderSource.data();

		int vssize = (int)vertexShaderSource.size();

		glShaderSource(vs, 1, &vsSource, &vssize);
		glCompileShader(vs);

		CheckShaderCompilation(vs);


		int fssize = (int)fragShaderSource.size();
		glShaderSource(fs, 1, &fsSource, &fssize);
		glCompileShader(fs);

		CheckShaderCompilation(fs);





		m_Program = glCreateProgram();

		glAttachShader(m_Program, vs);
		glAttachShader(m_Program, fs);


		glLinkProgram(m_Program);

		CheckProgramLinkage(m_Program);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	Shader::~Shader()
	{
	}

	Shader::Shader(Shader&& other) noexcept
		:m_Uniforms(std::move(other.m_Uniforms))
	{
		this->m_Program = other.m_Program;
	}

	void Shader::Bind() const
	{
		glUseProgram(m_Program);
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& data)
	{
		glProgramUniformMatrix4fv(m_Program, GetUniformLocation(name), 1, GL_FALSE, &data[0][0]);

	}

	void Shader::SetVec3(const std::string& name, const glm::vec3& data)
	{
		glProgramUniform3f(m_Program, GetUniformLocation(name), data.x, data.y, data.z);
	}

	void Shader::SetInt(const std::string& name, const int data)
	{
		glProgramUniform1i(m_Program, GetUniformLocation(name), data);

	}

	void Shader::DeleteProgram()
	{
		glDeleteProgram(m_Program);
	}



	int Shader::GetUniformLocation(const std::string& name) const
	{
		auto found = m_Uniforms.find(name);

		if (found == m_Uniforms.end())
		{
			int loc = glGetUniformLocation(m_Program, name.c_str());
			if (loc == -1)
			{
				LOG_ERROR("[OPENGL][Shader Uniform]: No Uniform named {} found", name);
				return -1;
			}

			m_Uniforms[name] = loc; 
			
		}

		return m_Uniforms.at(name);
	}










	static void CheckShaderCompilation(uint32_t shaderhandle)
	{
		int params = -1;
		glGetShaderiv(shaderhandle, GL_COMPILE_STATUS, &params);

		if (GL_TRUE != params) {

			int log_length;
			glGetShaderiv(shaderhandle, GL_INFO_LOG_LENGTH, &log_length);

			char* log = (char*)alloca(log_length);

			glGetShaderInfoLog(shaderhandle, 2048, &log_length, log);
			LOG_ERROR("[OPENGL][Shader Compilation]: {}", log);
		}
	}
	static void CheckProgramLinkage(uint32_t programhandle)
	{
		int params = -1;
		glGetProgramiv(programhandle, GL_LINK_STATUS, &params);

		if (GL_TRUE != params) {

			int log_length;
			glGetProgramiv(programhandle, GL_INFO_LOG_LENGTH, &log_length);

			char* log = (char*)alloca(log_length);

			glGetProgramInfoLog(programhandle, 2048, &log_length, log);
			LOG_ERROR("[OPENGL][Shader Compilation]: {}", log);

		}
	}


}