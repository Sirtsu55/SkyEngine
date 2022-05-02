#pragma once
#include "VertexData.h"
#include "Camera.h"
#include "Material.h"


namespace sky
{
	struct MeshConfig
	{
		std::string MeshFile;
		bool Material = false;
		
	};


	class Mesh
	{
	public:
		Mesh(MeshConfig& config);
		~Mesh();

		Mesh(Mesh&) = delete;
		Mesh& operator=(Mesh&) = delete;

		void Draw();


		glm::mat4 GetMVP() const { return Camera::GetActiveCamera().GetViewProjMatRef() * Transform; }
		glm::mat4 Transform;


	private:

		gltfAttribute GetAttributeLocFromAccessor(const fx::gltf::Document& doc, int accessor_idx);

		void CreateMaterial(const fx::gltf::Material& mat, const fx::gltf::Document& doc);

		TextureInfo GetTextureData(const fx::gltf::Material::Texture& tex, const fx::gltf::Document& doc) const;


		void FreeTextureData(const TextureInfo& texinf) const;

		std::vector<VertexData> m_MeshData;
		std::vector<Material> m_Materials;



		
	};



}
