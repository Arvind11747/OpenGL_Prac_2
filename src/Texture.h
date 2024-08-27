#pragma once
#include <string>
#include <glad/glad.h>

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_width, m_height, m_nrChannels;

public:
	Texture(const std::string filePath, GLenum format, bool freeTexData = true);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

private:
	void GenerateTexture(unsigned int num = 1);
	void SetTextureParameters();
	void LoadTexture(const std::string filePath, GLenum format);

};