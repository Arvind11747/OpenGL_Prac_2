#include <glad/glad.h>
#include "vendor/stb/stb_image.h"

#include "Debug.h"
#include "Texture.h"

Texture::Texture(const std::string filePath, GLenum format, bool freeTexData)
	: m_RendererID(0),m_FilePath(filePath), m_LocalBuffer(nullptr), m_width(0), m_height(0), m_nrChannels(0)
{
	GenerateTexture();
	Bind();
	SetTextureParameters();

	LoadTexture(filePath, format);

	Unbind();
	if (m_LocalBuffer && freeTexData)
	{
		//free the texture data memory
		stbi_image_free(m_LocalBuffer);
		m_LocalBuffer = nullptr; //!Fixing dangling pointer
	}
}

Texture::~Texture()
{
	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
		m_LocalBuffer = nullptr; //!Fixing dangling pointer
	}

	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::GenerateTexture(unsigned int num)
{
	glGenTextures(num, &m_RendererID);
}

void Texture::SetTextureParameters()
{
	stbi_set_flip_vertically_on_load(true);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::LoadTexture(const std::string filePath, GLenum format)
{
	m_LocalBuffer = stbi_load(filePath.c_str(), &m_width, &m_height, &m_nrChannels, 0);
	if (m_LocalBuffer)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, m_LocalBuffer);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		Debug::Log("Failed to load texture");
	}

}
