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
	// PBR MATERIAL
	///////////////////////////////////////////////////////////////////////////////

	PBRMaterial::PBRMaterial(Shader* shader, Texture* albedo, Texture* normal, Texture* rough, Texture* metal, Texture* ao)
		: Material(shader)
	{
		m_Textures.emplace("albedo", albedo);
		m_Textures.emplace("normal", normal);
		m_Textures.emplace("rough", rough);
		m_Textures.emplace("metal", metal);
		m_Textures.emplace("ao", ao);
	}

	PBRMaterial::~PBRMaterial()
	{
	}

	void PBRMaterial::Bind() const
	{
		m_Textures.at("albedo")->Bind(0);
		m_Textures.at("normal")->Bind(1);
		m_Textures.at("rough")->Bind(2);
		m_Textures.at("metal")->Bind(3);
		m_Textures.at("ao")->Bind(4);
		m_Shader->SetUniformInt("albedo", 0);
		m_Shader->SetUniformInt("normal", 1);
		m_Shader->SetUniformInt("rough", 2);
		m_Shader->SetUniformInt("metal", 3);
		m_Shader->SetUniformInt("ao", 4);
	}
}