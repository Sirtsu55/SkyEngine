#pragma once
#include "Texture.h"
#include "Shader.h"

namespace sky
{
	class RenderCanvas
	{
	public:

		struct CreateInfo
		{
			glm::ivec2 Resolution;
		};
		struct GBuffer
		{
			uint32_t m_NormalsTex;
			uint32_t m_WorldPosTex;
			uint32_t m_AlbedoSpecTex; //color + specular
			uint32_t m_DepthBuffer; //Renderbuffer
		};

		RenderCanvas(const CreateInfo& cInfo);
		~RenderCanvas();

		RenderCanvas(const RenderCanvas&) = delete;

		void StartGBuffer();
		void StartDeferredShading(Sptr<Shader>& shdr);
		
		void Resize(const glm::vec2& res);

		uint32_t GetFinalImage() { return m_FinalImageTex; }



	private:
		//Helpers 
		void CreateGBuffer(const glm::ivec2& Resolution);
		void CreateDeferredBuffer(const glm::ivec2& Resolution);
		void CreateQuad();
		

		uint32_t m_GBufferFBO;
		uint32_t m_DeferredFBO;

		GBuffer m_Buffers;

		uint32_t m_FinalImageTex;
		uint32_t m_FinalImageDepth;

		uint32_t m_QuadVAO;
		uint32_t m_QuadVBO;
		uint32_t m_QuadEBO;
		
	
	};
}
