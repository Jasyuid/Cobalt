#include "cbpch.h"
#include "VertexArray.h"

#include "OpenGL.h"

namespace Cobalt
{
	VertexArray::VertexArray()
	{
		GLCall(glGenVertexArrays(1, &m_RendererID)); // Create vertex array object (VAO)
		GLCall(glBindVertexArray(m_RendererID)); // Bind vertex array
	}

	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_RendererID));
	}

	void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		// Go through each vertex elements so the vertex can be outlined
		Bind(); // Bind vertex array
		vb.Bind(); // Bind vertex buffer
		const auto& elements = layout.GetElements(); // Get elements from vertex array
		unsigned int offset = 0; // Current location in vertex layout
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i]; // Get element
			GLCall(glEnableVertexAttribArray(i));

			// (Index of element, Number of components in elements Element type, Element normalized?, 
			//  Offset between this element and the corresponding one in the next vertex(size of the total vertex), 
			//  offset from beginning of vertex)
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
			offset += element.count * VertexBufferElement::GetSizeOfType(element.type); // Increase offset by element size and quantity
		}
	}

	// Bind functions
	void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(m_RendererID));
	}
	void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}

}
