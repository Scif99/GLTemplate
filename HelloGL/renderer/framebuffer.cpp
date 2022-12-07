#include "framebuffer.h"

Framebuffer::Framebuffer(unsigned int width, unsigned int height)
{
	glGenFramebuffers(1, &m_frame_buffer_ID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frame_buffer_ID);

	AttachTextureObject(width, height);
	AttachRenderbufferObject();

	//Check we have successufully set up the framebuffer
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0); //make sure to unbind to we dont accidentally render to wrong framebuffer
}

Framebuffer::~Framebuffer()
{
	glDeleteRenderbuffers(1, &m_renderbuffer_ID);
	glDeleteTextures(1, &m_texturebuffer_ID);
	glDeleteFramebuffers(1, &m_frame_buffer_ID);
}

//Attach a texture image as a color attachment (since we probably want to read color values in shader)
void Framebuffer::AttachTextureObject(int width, int height)
{

	// generate texture
	glGenTextures(1, &m_texturebuffer_ID);
	glBindTexture(GL_TEXTURE_2D, m_texturebuffer_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); //note the texture has no data (it is added when we render to framebuffer!)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Clamp so we dont get any weird wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0); //unbind texture after allocating memory

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_texturebuffer_ID, 0);
}

//Attach a renderbuffer object image as the stencil/depth attachments 
void Framebuffer::AttachRenderbufferObject()
{
	glGenRenderbuffers(1, &m_renderbuffer_ID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer_ID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glBindRenderbuffer(GL_RENDERBUFFER, 0); //unbind after allocating memory

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbuffer_ID); //attach to the stencil&depth attachments (can do it in one go!)
}