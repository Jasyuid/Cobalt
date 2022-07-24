#pragma once

#include "Buffer.h"
#include "VertexBufferLayout.h"

namespace Cobalt
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		// Bind functions
		void Bind() const;
		void Unbind() const;

	private:
		unsigned int m_RendererID; // Array buffer ID
	};

}