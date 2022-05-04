#pragma once

namespace sky
{
	class Shader
	{
	public:

		
		/*
		path = Points to a file with.glsl ending. Expects the shader files to have .glsl.frag and .glsl.vert
			For example if path = triangle.glsl, this class will search for triangle.glsl.frag and triangle.glsl.vert

		*/
		Shader(const std::string& path);
		Shader() = default;
		~Shader();

		Shader(Shader&& other) noexcept;


		//Shader(Shader&) = default;
		//Shader& operator=(Shader&) = default;

		void Bind() const;
		
		void SetMat4(const std::string& name, const glm::mat4& data);
		void SetVec3(const std::string& name, const glm::vec3& data);
		void SetInt(const std::string& name, const int data);


		void DeleteProgram();
	private:

		mutable std::unordered_map<std::string, uint32_t> m_Uniforms;

		int GetUniformLocation(const std::string& name) const;
		uint32_t m_Program = 0;
	};
}
