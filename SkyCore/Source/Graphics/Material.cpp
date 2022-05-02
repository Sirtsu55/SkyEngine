#include "SkyCore.h"
#include "Material.h"

namespace sky
{







    Material::Material(const MaterialInfoData& matInfo)
        :m_Sdr("Shaders/BasicColored.glsl")
    {
        m_Sdr.SetVec3("Color", matInfo.BaseColor);


        if (!matInfo.AlbedoTex.SampleInfo.empty())
        {
            m_Textures.emplace_back(matInfo.AlbedoTex);
        }
        //TODO: add more of the pbr textures
        
        
        Initialized = true;
    }

    Material::~Material()
    {
    }

    Material::Material(Material&& other) noexcept
        : m_Sdr(std::move(other.m_Sdr))
    {
        other.Initialized = false;
        this->Initialized = true;
        this->m_Textures = std::move(other.m_Textures);
    }



    void Material::Bind()
    {

        m_Sdr.Bind();
        for (int i = 0; i < m_Textures.size(); i++)
        {
            m_Textures.at(i).Bind(i);
            m_Sdr.SetInt("AlbedoTex", i);
        }
    }

    void Material::SetBaseColor(const glm::vec3& color)
    {
        m_Sdr.SetVec3("Color", color);
    }

    void Material::SetMVP(const glm::mat4& mvp)
    {
        m_Sdr.SetMat4("MVP", mvp);
    }



    
}