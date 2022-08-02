#include "cbpch.h"
#include "Mesh.h"

#include "OpenGL.h"

namespace Cobalt
{
	Mesh::Mesh(const float* v_data, unsigned int v_count, const VertexBufferLayout& layout, const unsigned int* i_data, unsigned int i_count, std::shared_ptr<Material> material)
		: m_VAO(), m_VBO(v_data, v_count * sizeof(float)), m_IBO(i_data, i_count)
	{
		m_VAO.AddBuffer(m_VBO, layout);
	}
	
	Mesh::~Mesh()
	{
	}

	void Mesh::Draw(std::shared_ptr<Material> material)
	{
		material->Bind();
		
		m_VAO.Bind();
		m_IBO.Bind();


		glDrawElements(GL_TRIANGLES, m_IBO.GetCount(), GL_UNSIGNED_INT, nullptr);
	}
}