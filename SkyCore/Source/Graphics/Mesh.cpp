
#include "SkyCore.h"
#include <fxgltf/fxgltf.h>
#include "Mesh.h"


namespace sky
{
	Mesh::Mesh(MeshConfig& config)
	{
		bool binary = config.MeshFile.ends_with("glb");

		std::string err;
		std::string warn;

		fx::gltf::Document meshdoc = binary ? fx::gltf::LoadFromBinary(config.MeshFile) : fx::gltf::LoadFromText(config.MeshFile);

		
		size_t finish = config.MeshFile.find_last_of("/");

		m_MeshFolder = config.MeshFile.substr(0, finish + 1);

		if (!err.empty())
		{
			LOG_ERROR("[GLTF File ERROR]: {}", err);
		}
		if (!warn.empty())
		{
			LOG_WARN("[GLTF File Warning]: {}", warn);
		}
		for (auto& mesh : meshdoc.meshes)
		{
			for (auto& prim : mesh.primitives)
			{
				if (prim.mode != fx::gltf::Primitive::Mode::Triangles)
				{
					continue;
				}
				uint32_t pos_idx = prim.attributes.at("POSITION");
				uint32_t norms_idx = prim.attributes.at("NORMAL");
				uint32_t texc_idx = prim.attributes.at("TEXCOORD_0");

				//TODO: All meshes dont have all of these attributes, so have to add error checking
				gltfAttribute vertLoc = GetAttributeLocFromAccessor(meshdoc, pos_idx);
				gltfAttribute normalLoc = GetAttributeLocFromAccessor(meshdoc, norms_idx);
				gltfAttribute texcLoc = GetAttributeLocFromAccessor(meshdoc, texc_idx);
				gltfAttribute indices = GetAttributeLocFromAccessor(meshdoc, prim.indices);

				m_MeshData.emplace_back(vertLoc, normalLoc, texcLoc, indices);

				
				//TODO: primtives can have same material so avoid duplicates

				auto& material = meshdoc.materials[prim.material];


				CreateMaterial(material, meshdoc);



			}
		}
		
	}


	Mesh::~Mesh()
	{

	}


	void Mesh::Draw()
	{
		for (int i = 0; i < m_MeshData.size(); i++)
		{
			Material& mat = m_Materials.at(i);
			VertexData& mesh = m_MeshData.at(i);



			mat.SetMVP(GetMVP());
			mat.Bind();
			mesh.Draw();

			
		}
	}

	gltfAttribute Mesh::GetAttributeLocFromAccessor(const fx::gltf::Document& doc, int accessor_idx)
	{
		auto& accessor = doc.accessors[accessor_idx];

		auto& bufview = doc.bufferViews.at(accessor.bufferView);


		auto& buffer = doc.buffers[bufview.buffer];

		const uint8_t* dataptr = &buffer.data[bufview.byteOffset + accessor.byteOffset];
		
		
		return { dataptr, bufview.byteLength, accessor.count, bufview.byteStride ,accessor.componentType, accessor.type };
	}


	void Mesh::CreateMaterial(const fx::gltf::Material& mat, const fx::gltf::Document& doc) 
	{
		MaterialInfoData mInfo{};

		//TODO: add more of the pbr textures
		if (!mat.pbrMetallicRoughness.baseColorTexture.empty())
		{
			mInfo.AlbedoTex = GetTextureData(mat.pbrMetallicRoughness.baseColorTexture, doc);
			
		}
		else
		{
			mInfo.AlbedoTex.SampleInfo = {};
		}




		m_Materials.emplace_back(mInfo);
		FreeTextureData(mInfo.AlbedoTex);
	}

	TextureInfo Mesh::GetTextureData(const fx::gltf::Material::Texture& tex, const fx::gltf::Document& doc) const
	{
		TextureInfo outInf{};
		
		auto& texInfo = doc.textures[tex.index];
		auto& img = doc.images[texInfo.source];
		auto& sampler = doc.samplers[texInfo.sampler];
		
		if (img.uri.empty()) //if empty, tex is in buffer view
		{
			auto& bufview = doc.bufferViews[img.bufferView];

			auto& buffer = doc.buffers[bufview.buffer];
			const uint8_t* dataStart = &buffer.data[bufview.byteOffset];

			//Decode Image


			int x, y, channels;


			outInf.dataptr = stbi_load_from_memory(dataStart, bufview.byteLength, &x, &y, &channels, 0);


			outInf.Size = glm::ivec2(x, y);
			outInf.Channels = channels;

			
			
		}
		else // if it is an external texture, then load from stbi
		{
			int x, y, channels;

			outInf.dataptr = stbi_load((m_MeshFolder + img.uri).c_str() , &x, &y, &channels, 0);
			
			outInf.Size = glm::ivec2(x, y);
			outInf.Channels = channels;
		}

		if (sampler.empty())
		{
			using namespace fx::gltf;
			outInf.SampleInfo = Texture::s_DefaultSampler;

		}
		else
		{
			outInf.SampleInfo = sampler;
		}

		return outInf;

	}

	void Mesh::FreeTextureData(const TextureInfo& texinf) const
	{
		stbi_image_free((void*)texinf.dataptr);
	}


}