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

class InstancingScene : public Scene
{
public:
	GLFWwindow& m_window;
	GLShader m_quad_shader;
	GLTexture m_quad_texture;

	Quad m_quad;

	std::shared_ptr<VertexBuffer> m_InstanceVBO;

	std::array<float, 200> m_translations;


public:
	InstancingScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Render() override;
	void Update(float dt) override;
};