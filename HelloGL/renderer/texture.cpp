#include "texture.h"

GLTexture::GLTexture(const std::string& filePath, bool flip /*= true*/)
	:m_path{filePath}
{
	if (flip) { stbi_set_flip_vertically_on_load(1); }

	int channels;
	//load image into buffer
	stbi_uc* data = NULL;
	data = stbi_load(filePath.c_str(), &m_width, &m_height, &channels, 0);
	if (!data)
	{
		std::cout << "Failed to load texture\n";
		return;
	}
	GLenum internal_format = 0, data_format = 0;
	if (channels == 3)
	{
		internal_format = GL_RGB8;
		data_format = GL_RGB;
	}
	else if (channels == 4)
	{
		internal_format = GL_RGBA8;
		data_format = GL_RGBA;
	}

	//gen/bind buffers
	glGenTextures(1, &m_renderer_ID.m_ID);
	glBindTexture(GL_TEXTURE_2D, m_renderer_ID.m_ID);

	// set the texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);


	glTexImage2D(GL_TEXTURE_2D, 0, internal_format, m_width, m_height, 0, data_format, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

//Overload for framebuffers
GLTexture::GLTexture(int width, int height)
	:m_width{width}, m_height{height}
{

	// generate texture
	glGenTextures(1, &m_renderer_ID.m_ID);
	glBindTexture(GL_TEXTURE_2D, m_renderer_ID.m_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); //note the texture has no data (it is added when we render to framebuffer!)
	//Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Set wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0); //unbind texture after allocating memory

}


//Bind texture to a specified texture unit
void GLTexture::Bind(unsigned int slot) const
{
	assert(slot >= 0);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_renderer_ID.m_ID);
}


