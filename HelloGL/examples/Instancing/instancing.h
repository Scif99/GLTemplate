#pragma once
#include <array>
#include <memory>

#include "../renderer/renderer.h"
#include "../camera.h"
#include "../scene.h"
#include "../light.h"
#include "../gui.h"

#include "../Shapes/cube.h"
#include "../Shapes/terrain.h"
#include "../Shapes/2Dquad.h"

constexpr int NUM_PARTICLES{ 100 };

class InstancingScene : public Scene
{
public:
	GLFWwindow& m_window;
	GLShader m_quad_shader;
	GLTexture m_quad_texture;

	std::array<float,4 * NUM_PARTICLES> m_data;

	unsigned int VBO;
	unsigned int VAO;


public:
	InstancingScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Render() override;
	void Update(float dt) override;
};