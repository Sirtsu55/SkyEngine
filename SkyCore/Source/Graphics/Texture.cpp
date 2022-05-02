#include "SkyCore.h"
#include "Texture.h"


namespace sky
{
	Texture::Texture(const TextureInfo& info)
	{

			glCreateTextures(GL_TEXTURE_2D, 1, &m_GLTex);

			auto [InternalFormat, Format] = GetFormatFromChannels(info.Channels);

			glTextureParameteri(m_GLTex, GL_TEXTURE_WRAP_S, (int)info.SampleInfo.wrapS);
			glTextureParameteri(m_GLTex, GL_TEXTURE_WRAP_T, (int)info.SampleInfo.wrapT);
			glTextureParameteri(m_GLTex, GL_TEXTURE_MIN_FILTER, (int)info.SampleInfo.minFilter);
			glTextureParameteri(m_GLTex, GL_TEXTURE_MAG_FILTER, (int)info.SampleInfo.magFilter);

			glTextureStorage2D(m_GLTex, info.MipMaps, InternalFormat, info.Size.x, info.Size.y);
			glTextureSubImage2D(m_GLTex, 0, 0, 0, info.Size.x, info.Size.y, Format, GL_UNSIGNED_BYTE, info.dataptr);
	}
	Texture::~Texture()
	{
		if (m_GLTex != -1)
		{
			glDeleteTextures(1, &m_GLTex);
		}
	}


	Texture::Texture(Texture&& other) noexcept
	{
		other.m_GLTex = -1;
		this->m_GLTex = other.m_GLTex;
	}

	void Texture::Bind(int unit)
	{
		glBindTextureUnit(unit, m_GLTex);
	}

	void Texture::UnBind()
	{
		glBindTextureUnit(0, 0);
	}

	std::tuple<uint32_t, uint32_t> Texture::GetFormatFromChannels(uint32_t channels)
	{
		uint32_t internalF, Format;

		switch (channels)
		{
		case 1:
		{
			internalF = GL_R8;
			Format = GL_RED;
			break;
		}
		case 2:
		{
			internalF = GL_R8;
			Format = GL_RG;
			break;
		}
		case 3:
		{
			internalF = GL_RGB8;
			Format = GL_RGB;
			break;
		}
		case 4:
		{
			internalF = GL_RGBA8;
			Format = GL_RGBA;
			break;
		}

		}

		return {internalF, Format };
	}

}