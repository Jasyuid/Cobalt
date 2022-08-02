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
}