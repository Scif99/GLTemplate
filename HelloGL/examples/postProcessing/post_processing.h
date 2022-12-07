#pragma once

#include <memory>
#include "../renderer/renderer.h"
#include "../camera.h"
#include "../cube.h"
#include "../terrain.h"
#include "../quad.h"
#include "../scene.h"

class PostProcessingScene
{
public:
	GLFWwindow& m_window;

	GLShader m_container_shader;
	GLShader m_light_source_shader;
	GLShader m_frame_buffer_shader;

	GLTexture m_container_diffuse;
	GLTexture m_container_specular;
	GLTexture m_tiles;

	Camera m_camera;

	std::unique_ptr<Container> m_container;
	std::unique_ptr<LightCube> m_light;
	std::unique_ptr<Terrain>	m_terrain;

	//Framebuffer stuff
	std::unique_ptr<Quad> m_frame_quad;
	Framebuffer m_framebuffer;

public:
	PostProcessingScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy);
	void Update(float dt);
	void Render();

};