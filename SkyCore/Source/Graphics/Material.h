#include "SkyCore.h"
#include "Shader.h"
#include "Texture.h"

namespace sky
{


	struct MaterialInfoData
	{
		glm::vec4 BaseColor = glm::vec4(1.0f);
		TextureInfo NormTex;
		TextureInfo AlbedoTex;
	};


	class Material
	{
	public:

		Material(const MaterialInfoData& matInfo);
		Material() = default;
		~Material();



		Material(Material&& other) noexcept;


		Material(Material&) = delete;
		Material& operator=(Material&) = delete;

		void Bind();
		void SetBaseColor(const glm::vec3& color);
		void SetMVP(const glm::mat4& mvp);
	private:

		bool Initialized = false;
		Shader m_Sdr;

		std::vector<Texture> m_Textures;
	};

}