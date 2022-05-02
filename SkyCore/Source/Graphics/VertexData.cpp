#include "SkyCore.h"
#include "VertexData.h"


namespace sky
{


	VertexData::VertexData(const gltfAttribute& vertices,
		const gltfAttribute& normals,
		const gltfAttribute& texcoords,
		const gltfAttribute& indices
	) 
		:m_IndicesCount(indices.Count), m_IndicesDataType((uint32_t)indices.DataType)
	{


		glCreateVertexArrays(1, &m_VAO);
		glCreateBuffers(1, &m_VerticesBO);
		glCreateBuffers(1, &m_NormalsBO);
		glCreateBuffers(1, &m_TexcBO);

		glNamedBufferStorage(m_VerticesBO, vertices.ByteLength, vertices.Loc, GL_DYNAMIC_STORAGE_BIT);

		glNamedBufferStorage(m_NormalsBO, normals.ByteLength, normals.Loc, GL_DYNAMIC_STORAGE_BIT);

		glNamedBufferStorage(m_TexcBO, texcoords.ByteLength, texcoords.Loc, GL_DYNAMIC_STORAGE_BIT);



		glVertexArrayVertexBuffer(m_VAO, 0, m_VerticesBO, 0, GetGLDataTypeSize(vertices.DataType) * (int)vertices.NumComponents);
		glVertexArrayAttribFormat(m_VAO, 0, (int)vertices.NumComponents, GL_FLOAT, GL_FALSE, 0);
			
		glVertexArrayVertexBuffer(m_VAO, 1, m_NormalsBO, 0, GetGLDataTypeSize(normals.DataType) * (int)normals.NumComponents);
		glVertexArrayAttribFormat(m_VAO, 1, (int)normals.NumComponents, GL_FLOAT, GL_FALSE, 0);
							
		glVertexArrayVertexBuffer(m_VAO, 2, m_TexcBO, 0, GetGLDataTypeSize(texcoords.DataType) * (int)texcoords.NumComponents);
		glVertexArrayAttribFormat(m_VAO, 2, (int)texcoords.NumComponents, GL_FLOAT, GL_FALSE, 0);



		glVertexArrayAttribBinding(m_VAO, 0, 0);
		glVertexArrayAttribBinding(m_VAO, 1, 1);
		glVertexArrayAttribBinding(m_VAO, 2, 2);

		glEnableVertexArrayAttrib(m_VAO, 0);
		glEnableVertexArrayAttrib(m_VAO, 1);
		glEnableVertexArrayAttrib(m_VAO, 2);


		//Element Buffer
		glCreateBuffers(1, &m_EBO);

		glNamedBufferStorage(m_EBO, indices.ByteLength, indices.Loc, 0u);

		glVertexArrayElementBuffer(m_VAO, m_EBO);

		Initialized = true;

	}

	


	VertexData::~VertexData()
	{
		if (Initialized)
		{
			glDeleteBuffers(1, &m_VerticesBO);
			glDeleteBuffers(1, &m_NormalsBO);
			glDeleteBuffers(1, &m_TexcBO);
			glDeleteBuffers(1, &m_EBO);
			glDeleteVertexArrays(1, &m_VAO);
		}
	}


	VertexData::VertexData(VertexData&& other) noexcept
	{
		this->m_VAO = other.m_VAO;
		this->m_VerticesBO = other.m_VerticesBO;
		this->m_NormalsBO = other.m_NormalsBO;
		this->m_TexcBO = other.m_TexcBO;
		this->m_EBO = other.m_EBO;

		this->m_IndicesCount = other.m_IndicesCount;
		this->m_IndicesDataType = other.m_IndicesDataType;
		this->Initialized = true;
		other.Initialized = false;
	}

	void VertexData::Draw() const
	{
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, m_IndicesCount, m_IndicesDataType, nullptr);
	}
	uint32_t GetGLDataTypeSize(fx::gltf::Accessor::ComponentType type)
	{


		switch (type)
		{
		case fx::gltf::Accessor::ComponentType::Byte:
			return sizeof(char8_t);
		case fx::gltf::Accessor::ComponentType::UnsignedByte:
			return sizeof(char8_t);
		case fx::gltf::Accessor::ComponentType::Short:
			return sizeof(int16_t);
		case fx::gltf::Accessor::ComponentType::UnsignedShort:
			return sizeof(uint16_t);
		case fx::gltf::Accessor::ComponentType::UnsignedInt:
			return sizeof(uint32_t);
		case fx::gltf::Accessor::ComponentType::Float:
			return sizeof(float_t);

		}

		throw std::runtime_error("Data Type not supported");
		
	}

}