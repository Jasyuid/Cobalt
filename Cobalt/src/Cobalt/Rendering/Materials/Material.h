#pragma once

#include "../Shader.h"
#include "../Texture.h"

#include <unordered_map>

namespace Cobalt
{
	typedef std::unordered_map<std::string, Texture*> TextureMap;

	class Material
	{
	public:
		Material(Shader* shader) : m_Shader(shader) {};
		~Material() {};

		virtual void Bind() const = 0;
		
		inline Shader* GetShader() const { return m_Shader; }

	protected:
		Shader* m_Shader;
	};

	class BasicMaterial : public Material
	{
	public:
		BasicMaterial(Shader* shader);
		~BasicMaterial();

		void Bind() const override;
	};

	class TextureMaterial : public Material
	{
	public:
		TextureMaterial(Shader* shader, Texture* texture);
		~TextureMaterial();

		void Bind() const override;
	protected:
		Texture* m_Texture;
	};
}