#include "cbpch.h"
#include "Texture.h"

#include "OpenGL.h"
#include <stb_image.h>

namespace Cobalt
{
	Texture::Texture(const std::string& filepath, bool flip)
		: m_RendererID(0), m_FilePath(filepath), m_LocalBuffer(nullptr),
		m_Width(0), m_Height(0), m_BPP(0)
	{
		// Load texture into buffer
		stbi_set_flip_vertically_on_load(flip);
		m_LocalBuffer = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

		// Exit if file not found
		if (!m_LocalBuffer)
		{
			CB_WARN("Unable to find {0}!", filepath);
			return;
		}

		// Generate texture
		glGenTextures(1,&m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		// Set texture settings
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// Create texture from buffer
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);

		glBindTexture(GL_TEXTURE_2D, 0);

		// Free buffer
		if (m_LocalBuffer)
		{
			stbi_image_free(m_LocalBuffer);
		}
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	// Bind functions
	void Texture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}
	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}


