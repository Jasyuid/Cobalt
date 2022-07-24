#pragma once

#include "VertexArray.h"

namespace Cobalt
{
	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		void Draw();

	private:
		VertexArray m_VAO;
		VertexBuffer m_VBO;
		IndexBuffer m_IBO;

	};
}