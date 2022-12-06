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