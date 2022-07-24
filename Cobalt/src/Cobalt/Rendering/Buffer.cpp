#include "cbpch.h"
#include "Buffer.h"

#include "OpenGL.h"

namespace Cobalt
{
///////////////////////////////////////////////////////////////////////////////
// VERTEX BUFFER
///////////////////////////////////////////////////////////////////////////////

	VertexBuffer::VertexBuffer(const float* data, unsigned int size)
		: m_RendererID(0), m_Size(size)
	{
		GLCall(glGenBuffers(1, &m_RendererID)); // Generate a new buffer (VBO)
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // Bind the new buffer

		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); // Send vertices to static buffer
	}

	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_RendererID)); 
	}

	// Bind functions
	void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}
	void VertexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}


///////////////////////////////////////////////////////////////////////////////
// INDEX BUFFER
///////////////////////////////////////////////////////////////////////////////

	IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
		: m_RendererID(0), m_Count(count), m_Dynamic(false)
	{
		GLCall(glGenBuffers(1, &m_RendererID)); // Generate a new buffer (IBO)
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); // Bind the new buffer

		// TODO: Possibly change unsigned int
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW)); // Send indicies to static buffer
	}

	IndexBuffer::~IndexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

	// Bind functions
	void IndexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}
	void IndexBuffer::Unbind() const
	{
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

}

