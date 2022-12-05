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


//A material holds a shader and the associated diffuse/specular maps...
struct Material
{
	std::shared_ptr<GLShader> m_shader;

	std::shared_ptr<GLTexture> m_diffuse_map;
	std::shared_ptr<GLTexture> m_specular_map;
};

class LightSource
{
public:
	glm::vec3 m_position;

	glm::vec3 m_ambient;
	glm::vec3 m_diffuse;
	glm::vec3 m_specular;

public:
	LightSource(const glm::vec3& pos, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
		: m_position{ pos }, m_ambient{ ambient }, m_diffuse{ diffuse }, m_specular{ specular } {}

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

	std::unique_ptr<Camera> m_camera;

	std::unique_ptr<LightSource> m_light;


	//Camera m_camera;
	std::unique_ptr<VertexArray> m_VAO;


	Application(unsigned int width, unsigned int height);
	~Application();

	void init();
	void ProcessInput(GLFWwindow* window, float dt, float dx, float dy);
	void Update(float dt);
	void Render();

};