#pragma once

#include "VertexArray.h"
#include "Texture.h"
#include "Shader.h"

namespace Cobalt
{
	typedef std::unordered_map<std::string, Texture*> TextureMap;
	
	class Mesh
	{
	public:
		Mesh(const float* v_data, unsigned int v_count, const VertexBufferLayout& layout, const unsigned int* i_data, unsigned int i_count, TextureMap tex_map);
		~Mesh();

		void Draw(Shader* shader);

	private:
		VertexArray m_VAO; // Mesh vertex array
		VertexBuffer m_VBO; // Mesh vertex buffer
		IndexBuffer m_IBO; // Mesh index buffer

		Shader* m_Shader; // Mesh shader

		TextureMap m_Textures; // Mesh texture maps
	};
}