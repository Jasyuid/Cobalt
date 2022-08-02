#pragma once

#include "VertexArray.h"
#include "Materials/Material.h"

#include <unordered_map>

namespace Cobalt
{	
	class Mesh
	{
	public:
		Mesh(const float* v_data, unsigned int v_count, const VertexBufferLayout& layout, const unsigned int* i_data, unsigned int i_count, Material* material);
		~Mesh();

		void Draw(Material* material);

	private:
		VertexArray m_VAO; // Mesh vertex array
		VertexBuffer m_VBO; // Mesh vertex buffer
		IndexBuffer m_IBO; // Mesh index buffer
	};
}