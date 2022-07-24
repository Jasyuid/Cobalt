#pragma once

#include "OpenGL.h"

namespace Cobalt
{
	struct VertexBufferElement
	{
		unsigned int type; // Data type of element
		unsigned int count; // Quantity of data type
		unsigned int normalized; // Is data normalized

		// Get the size of one piece of the elements in bytes
		static unsigned int GetSizeOfType(unsigned int type)
		{
			switch (type)
			{
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 4;
			}
			CB_CORE_ASSERT(false, "Unsupported type being used in VertexBufferElement!");
			return 0;
		}
	};

	// Vertex layout for create a vertex array object
	class VertexBufferLayout
	{
	public:
		VertexBufferLayout()
			:m_Stride(0) {};

		// Push element to the layout
		template<typename T>
		void Push(unsigned int count)
		{
			static_assert(false);
		}

		// Push float
		template<>
		void Push<float>(unsigned int count)
		{
			m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
		}

		// Push unsigned int
		template<>
		void Push<unsigned int>(unsigned int count)
		{
			m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		}

		// Push unsigned byte
		template<>
		void Push<unsigned char>(unsigned int count)
		{
			m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
			m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		}

		inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }
		inline unsigned int GetStride() const { return m_Stride; }

	private:
		std::vector<VertexBufferElement> m_Elements; // All the elements that make up each vertex
		unsigned int m_Stride; // The byte length of each vertex
	};

}
