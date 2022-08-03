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
	private:
		Texture* m_Texture;
	};

	class ColorMaterial : public Material
	{
	public:
		ColorMaterial(Shader* shader, glm::vec3 albedo, float rough, float metal, float ao);
		~ColorMaterial();

		void Bind() const override;
	private:
		glm::vec3 m_Albedo;
		float m_Rough, m_Metal, m_AO;
	};

	class PBRMaterial : public Material
	{
	public:
		PBRMaterial(Shader* shader, Texture* albedo, Texture* normal, Texture* rough, Texture* metal, Texture* ao);
		~PBRMaterial();

		void Bind() const override;
	private:
		TextureMap m_Textures;
	};
}