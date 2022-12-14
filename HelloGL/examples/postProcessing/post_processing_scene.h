#pragma once

#include "camera.h"
#include "scene.h"
#include "light.h"

#include "renderer/framebuffer.h"
#include "renderer/buffer.h"
#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/vertex_array.h"

#include "Shapes/cube.h"
#include "Shapes/grid.h"
#include "Shapes/2Dquad.h"

class PostProcessingScene : public Scene
{
public:
	GLFWwindow& m_window;

	GLShader m_material_shader;
	GLShader m_light_source_shader;
	GLShader m_frame_buffer_shader;

	GLTexture m_container_diffuse_map;
	GLTexture m_container_specular_map;
	GLTexture m_tiles_texture;

	CubeMesh m_container;
	LightCube m_light;
	Grid m_terrain;

	//Framebuffer stuff
	Quad m_frame_quad;
	Framebuffer m_framebuffer;

public:
	PostProcessingScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Update(float dt) override;
	void Render() override;

};