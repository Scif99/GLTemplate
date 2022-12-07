#pragma once

#include "camera.h"
#include "resource_manager.h"
#include "2d_sprite_renderer.h"
#include "renderer/renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "cube.h"
#include "gui.h"
#include "terrain.h"

class Framebuffer
{
	enum class Target
	{
		READ,
		WRITE,
		BOTH
	};


	unsigned int m_ID;

	Framebuffer(int width, int height)
	{
		glGenFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		AttachTextureObject(width, height);
		AttachRenderbufferObject();

		//Check we have successufully set up the framebuffer
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0); //make sure to unbind to we dont accidentally render to wrong framebuffer
	}

	//Attach a texture image as a color attachment (since we probably want to read color values in shader)
	void AttachTextureObject(int width, int height)
	{

		// generate texture
		unsigned int textureColorbuffer;
		glGenTextures(1, &textureColorbuffer);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); //note the texture has no data (it is added when we render to framebuffer!)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0); //unbind texture after allocating memory

		// attach it to currently bound framebuffer object
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	}

	//Attach a renderbuffer object image as the stencil/depth attachments 
	void AttachRenderbufferObject()
	{
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
		glBindRenderbuffer(GL_RENDERBUFFER, 0); //unbind after allocating memory

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); //attach to the stencil&depth attachments (can do it in one go!)
	}

	void Bind() { glBindFramebuffer(GL_FRAMEBUFFER, m_ID); }
	void Unbind() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

	~Framebuffer() { glDeleteFramebuffers(1, &m_ID); }

};




class Application
{
public:


public:
	bool m_keys[1024];
	unsigned int m_width, m_height;


	std::unique_ptr<GLShader> m_container_shader;
	std::unique_ptr<GLShader> m_lightsourceshader;

	std::unique_ptr<GLTexture> m_diffuse_map;
	std::unique_ptr<GLTexture> m_specular_map;
	std::unique_ptr<GLTexture> m_tiles;


	std::unique_ptr<Camera> m_camera;

	std::unique_ptr<Container> m_container;
	std::unique_ptr<LightCube> m_light;
	std::unique_ptr<Terrain>	 m_terrain;

	//Window/gui stuff
	GLFWwindow* m_window; //TODO figure out how to use smart pointers...
	std::unique_ptr<GUI> m_gui;


	Application(unsigned int width, unsigned int height);
	~Application() {};

	void init(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy);
	void Update(float dt);
	void Render();
	 
	//Ensure that we cleanup anything that relies on glfw before glfw itself gets cleaned up
	void Cleanup();

};