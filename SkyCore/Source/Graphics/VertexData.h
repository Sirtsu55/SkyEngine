#pragma once

namespace sky
{

	struct gltfAttribute
	{
		const uint8_t* Loc;
		uint32_t ByteLength;
		uint32_t Count;

		uint32_t stride;

		fx::gltf::Accessor::ComponentType DataType;
		fx::gltf::Accessor::Type NumComponents;
	};

	class VertexData
	{
	public:

		VertexData(const gltfAttribute& vertices,
			const gltfAttribute& normals,
			const gltfAttribute& texcoords,
			const gltfAttribute& indices
		);



		~VertexData();
		VertexData(VertexData&) = delete;

		VertexData(VertexData&& other) noexcept;

		VertexData() = default;
		VertexData& operator=(VertexData&) = delete;


		enum class BindingLocation
		{
			Position = 0, Normals = 1, TexCoords = 2, VertexColor = 3
		};

		void Draw() const;

		uint32_t GetNumIndices() const { return m_IndicesCount; }
	private:
		uint32_t m_VerticesBO	;
		uint32_t m_NormalsBO	;
		uint32_t m_TexcBO		;

		uint32_t m_VAO;
		uint32_t m_VBO;
		uint32_t m_EBO;

		uint32_t m_IndicesCount;
		uint32_t m_IndicesDataType;


		bool Initialized = false;
	};


	static uint32_t GetGLDataTypeSize(fx::gltf::Accessor::ComponentType type);
}
