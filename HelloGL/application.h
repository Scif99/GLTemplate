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

class Application
{
public:


public:
	bool m_keys[1024];
	unsigned int m_width, m_height;

	std::unique_ptr<GLShader> m_shader;
	std::unique_ptr<GLTexture> m_texture;
	std::unique_ptr<Camera> m_camera;


	//Camera m_camera;
	std::unique_ptr<VertexArray> m_VAO;

	Application(unsigned int width, unsigned int height);
	~Application();

	void init();
	void ProcessInput(GLFWwindow* window, float dt, float dx, float dy);
	void Update(float dt);
	void Render();

};