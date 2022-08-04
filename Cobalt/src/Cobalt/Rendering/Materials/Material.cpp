#include "cbpch.h"
#include "Material.h"

#include "../OpenGL.h"

namespace Cobalt
{
	///////////////////////////////////////////////////////////////////////////////
	// BASIC MATERIAL
	///////////////////////////////////////////////////////////////////////////////

	BasicMaterial::BasicMaterial(Shader* shader)
		: Material(shader)
	{
	}

	BasicMaterial::~BasicMaterial()
	{
	}

	void BasicMaterial::Bind() const
	{
	}

	///////////////////////////////////////////////////////////////////////////////
	// TEXTURE MATERIAL
	///////////////////////////////////////////////////////////////////////////////

	TextureMaterial::TextureMaterial(Shader* shader, Texture* texture)
		: Material(shader), m_Texture(texture)
	{
	}

	TextureMaterial::~TextureMaterial()
	{
	}

	void TextureMaterial::Bind() const
	{
		m_Texture->Bind(0);
		m_Shader->SetUniformInt("diffuse", 0);
	}

	///////////////////////////////////////////////////////////////////////////////
	// COLOR MATERIAL
	///////////////////////////////////////////////////////////////////////////////

	ColorMaterial::ColorMaterial(Shader* shader, glm::vec3 albedo, float rough, float metal, float ao)
		: Material(shader), m_Albedo(albedo), m_Rough(rough), m_Metal(metal), m_AO(ao)
	{
	}

	ColorMaterial::~ColorMaterial()
	{
	}

	void ColorMaterial::Bind() const
	{
		m_Shader->SetUniformFloat3("albedo", m_Albedo);
		m_Shader->SetUniformFloat("roughness", m_Rough);
		m_Shader->SetUniformFloat("metallic", m_Metal);
		m_Shader->SetUniformFloat("ao", m_AO);
	}

	///////////////////////////////////////////////////////////////////////////////
	// PBR MATERIAL
	///////////////////////////////////////////////////////////////////////////////

	PBRMaterial::PBRMaterial(Shader* shader, Texture* albedo, Texture* normal, Texture* rough, Texture* metal, Texture* ao)
		: Material(shader)
	{
		m_Textures.emplace("albedo", albedo);
		m_Textures.emplace("normal", normal);
		m_Textures.emplace("roughness", rough);
		m_Textures.emplace("metallic", metal);
		m_Textures.emplace("ao", ao);
	}

	PBRMaterial::~PBRMaterial()
	{
	}

	void PBRMaterial::Bind() const
	{
		m_Textures.at("albedo")->Bind(0);
		m_Textures.at("normal")->Bind(1);
		m_Textures.at("roughness")->Bind(2);
		m_Textures.at("metallic")->Bind(3);
		m_Textures.at("ao")->Bind(4);
		m_Shader->SetUniformInt("albedoTex", 0);
		m_Shader->SetUniformInt("normalTex", 1);
		m_Shader->SetUniformInt("roughnessTex", 2);
		m_Shader->SetUniformInt("metallicTex", 3);
		m_Shader->SetUniformInt("aoTex", 4);
	}
}