#include "SkyCore.h"
#include "RenderCanvas.h"


namespace sky
{
	RenderCanvas::RenderCanvas(const CreateInfo& cInfo)
	{

		CreateGBuffer(cInfo.Resolution);
		CreateDeferredBuffer(cInfo.Resolution);
		CreateQuad();

	}


	RenderCanvas::~RenderCanvas()
	{
		glDeleteTextures(1, &m_Buffers.m_NormalsTex);
		glDeleteTextures(1, &m_Buffers.m_WorldPosTex);
		glDeleteTextures(1, &m_Buffers.m_AlbedoSpecTex);

		glDeleteFramebuffers(1, &m_GBufferFBO);
		glDeleteFramebuffers(1, &m_DeferredFBO);
	}

	void RenderCanvas::StartGBuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_GBufferFBO);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // keep it black so it doesn't leak into g-buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

	void RenderCanvas::StartDeferredShading(Sptr<Shader>& shdr)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_DeferredFBO);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindTextureUnit(m_Buffers.m_AlbedoSpecTex, 1);
		glBindTextureUnit(m_Buffers.m_NormalsTex, 2);
		glBindTextureUnit(m_Buffers.m_WorldPosTex, 3);

		
		shdr->SetInt("AlbedoSpec", 1);
		//shdr->SetInt("Normals", 2);
		//shdr->SetInt("WorldPos", 3);
		shdr->Bind();


		glBindVertexArray(m_QuadVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


	}



	void RenderCanvas::Resize(const glm::vec2& res)
	{
	}

	void RenderCanvas::CreateGBuffer(const glm::ivec2& Resolution)
	{
		glCreateFramebuffers(1, &m_GBufferFBO);


		// Mutable Texture, NON DSA way

		glCreateTextures(GL_TEXTURE_2D, 1, &m_Buffers.m_WorldPosTex);
		glBindTexture(GL_TEXTURE_2D, m_Buffers.m_WorldPosTex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, Resolution.x, Resolution.y, 0, GL_RGB, GL_FLOAT, 0);
		glNamedFramebufferTexture(m_GBufferFBO, GL_COLOR_ATTACHMENT0, m_Buffers.m_WorldPosTex, 0);


		glCreateTextures(GL_TEXTURE_2D, 1, &m_Buffers.m_NormalsTex);
		glBindTexture(GL_TEXTURE_2D, m_Buffers.m_NormalsTex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, Resolution.x, Resolution.y, 0, GL_RGB, GL_FLOAT, 0);
		glNamedFramebufferTexture(m_GBufferFBO, GL_COLOR_ATTACHMENT1, m_Buffers.m_NormalsTex, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_Buffers.m_AlbedoSpecTex);
		glBindTexture(GL_TEXTURE_2D, m_Buffers.m_AlbedoSpecTex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Resolution.x, Resolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
		glNamedFramebufferTexture(m_GBufferFBO, GL_COLOR_ATTACHMENT2, m_Buffers.m_AlbedoSpecTex, 0);



		glCreateRenderbuffers(1, &m_Buffers.m_DepthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, m_Buffers.m_DepthBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Resolution.x, Resolution.y);
		glNamedFramebufferRenderbuffer(m_GBufferFBO, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_Buffers.m_DepthBuffer);

		//							World pos				Normals				Albedo + Spec			Depth
		uint32_t attachments[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_DEPTH_ATTACHMENT };
		glNamedFramebufferDrawBuffers(m_GBufferFBO, 3, attachments);
	}

	void RenderCanvas::CreateDeferredBuffer(const glm::ivec2& Resolution)
	{
		glCreateFramebuffers(1, &m_DeferredFBO);


		glCreateTextures(GL_TEXTURE_2D, 1, &m_FinalImageTex);
		glBindTexture(GL_TEXTURE_2D, m_FinalImageTex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, Resolution.x, Resolution.y, 0, GL_RGBA, GL_FLOAT, 0);
		glNamedFramebufferTexture(m_DeferredFBO, GL_COLOR_ATTACHMENT0, m_FinalImageTex, 0);


		glCreateRenderbuffers(1, &m_FinalImageDepth);
		glBindRenderbuffer(GL_RENDERBUFFER, m_FinalImageDepth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Resolution.x, Resolution.y);
		glNamedFramebufferRenderbuffer(m_DeferredFBO, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_FinalImageDepth);


		//											Final Image
		uint32_t attachments[] = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT };
		glNamedFramebufferDrawBuffers(m_DeferredFBO, 1, attachments);
	}

	void RenderCanvas::CreateQuad()
	{
		float vertices[] = {
			// positions        // texture coords
			 1.0f,  1.0f, 1.0f, 1.0f,   // top right
			 1.0f, -1.0f, 1.0f, 0.0f,   // bottom right
			-1.0f, -1.0f, 0.0f, 0.0f,   // bottom left
			-1.0f,  1.0f, 0.0f, 1.0f    // top left 
		};
		unsigned int indices[] = {
			3, 1, 0, // first triangle
			3, 2, 1  // second triangle
		};

		glCreateVertexArrays(1, &m_QuadVAO);
		glCreateBuffers(1, &m_QuadVBO);
		glCreateBuffers(1, &m_QuadEBO);

		glNamedBufferStorage(m_QuadVBO, sizeof(vertices), vertices, 0);



		glVertexArrayVertexBuffer( m_QuadVAO, 0, m_QuadVBO, 0, 4 * sizeof(float));



		glVertexArrayAttribFormat(m_QuadVAO, 0, 2, GL_FLOAT, false, 0);
		glVertexArrayAttribFormat(m_QuadVAO, 1, 2, GL_FLOAT, false, 2 * sizeof(float));

		glVertexArrayAttribBinding(m_QuadVAO, 0, 0);
		glVertexArrayAttribBinding(m_QuadVAO, 1, 0);


		glEnableVertexArrayAttrib(m_QuadVAO, 0);
		glEnableVertexArrayAttrib(m_QuadVAO, 1);

		glCreateBuffers(1, &m_QuadEBO);

		glNamedBufferStorage(m_QuadEBO, sizeof(indices), indices, 0);

		glVertexArrayElementBuffer(m_QuadVAO, m_QuadEBO);


	}



}