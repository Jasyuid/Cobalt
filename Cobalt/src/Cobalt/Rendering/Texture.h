#pragma once

class Texture
{
public:
	Texture(const std::string& filepath, bool flip = false);
	~Texture();

	// Bind functions
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }

private:
	unsigned int m_RendererID; // Texture ID
	std::string m_FilePath; // File path for debugging
	unsigned char* m_LocalBuffer; // Buffer of texture data
	int m_Width, m_Height, m_BPP; // Texture properties
};