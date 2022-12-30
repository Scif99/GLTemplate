#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <iostream>
#include <string>

#include "gl_wrappers.h"
#include "stb_image.h"

class GLTexture
{
public:
	std::string m_path;
	GLID m_renderer_ID;
	int m_width{ 0 };
	int m_height{ 0 };

public:
	~GLTexture() { glDeleteTextures(1, &m_renderer_ID); }
	GLTexture() = default;
	GLTexture(const GLTexture& other) = default;
	GLTexture& operator=(const GLTexture& other) = default;
	GLTexture(GLTexture&& other) = default;
	GLTexture& operator=(GLTexture&& other) = default;


	GLTexture(const std::string& filePath, bool alpha, bool flip = true); //constructor for texture 
	GLTexture(int width, int height); //overload for framebuffers

	//Bind to a specified texture unit
	void Bind(unsigned int slot = 0) const;
	void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
};

#endif