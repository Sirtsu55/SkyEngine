#pragma once

namespace sky
{

	
	struct TextureInfo
	{
		uint8_t* dataptr = nullptr;
		fx::gltf::Sampler SampleInfo;
		uint32_t Channels = 0;
		uint32_t MipMaps = 1;

		glm::ivec2 Size;



	};

	class Texture
	{

	public:
		Texture(const TextureInfo& info);

		~Texture();

		Texture(Texture&) = delete;
		Texture& operator=(Texture&) = delete;

		Texture(Texture&& other) noexcept;

		void Bind(int unit);
		static void UnBind();

		
	private:

		uint32_t m_GLTex;

		std::tuple<uint32_t, uint32_t> GetFormatFromChannels(uint32_t channels);


	public:
		static inline const fx::gltf::Sampler s_DefaultSampler = { "",
				fx::gltf::Sampler::MagFilter::Linear,			//magFilter 
				fx::gltf::Sampler::MinFilter::Linear,			//minFilter 
				fx::gltf::Sampler::WrappingMode::Repeat,		//wrapS  
				fx::gltf::Sampler::WrappingMode::Repeat		//wrapT 
		};
	};
}
