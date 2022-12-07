#pragma once

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/**
TO-DO
- create classes for texture/renderbuffer?
- add options for read/write framebufffers
-

*/


class Framebuffer
{
public:
	unsigned int m_frame_buffer_ID;
	unsigned int m_texturebuffer_ID;
	unsigned int m_renderbuffer_ID;

	Framebuffer(unsigned int width, unsigned int height);

	//Attach a texture image as a color attachment (since we probably want to read color values in shader)
	void AttachTextureObject(int width, int height);

	//Attach a renderbuffer object image as the stencil/depth attachments 
	void AttachRenderbufferObject();

	void Bind() { glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_ID); }
	void Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

	~Framebuffer();

};