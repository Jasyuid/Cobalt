#pragma once

// Vertex buffer object
class VertexBuffer
{
public:
	VertexBuffer(const float* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int m_RendererID; // BufferID
	unsigned int m_Size; // Buffer size
};

// Index buffer object
class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }

private:
	unsigned int m_RendererID; // Buffer ID
	unsigned int m_Count; // Number of indicies
	bool m_Dynamic; // Buffer dynamic

};