#pragma once

#include <array>
#include <memory>

#include "camera.h"
#include "gui.h"
#include "scene.h"

#include "renderer/shader.h"
#include "renderer/texture.h"
#include "renderer/buffer.h"
#include "renderer/vertex_array.h"
#include "Shapes/2Dquad.h"

constexpr int NUM_PARTICLES{ 100 };

class BasicFountainScene : public Scene
{
public:
	GLFWwindow& m_window;
	GLShader m_quad_shader;
	GLTexture m_quad_texture;

	std::array<float,4 * NUM_PARTICLES> m_data;

	std::shared_ptr<VertexBuffer> m_VBO;
	std::shared_ptr<VertexArray> m_VAO;
	std::shared_ptr<IndexBuffer> m_IBO;

public:
	BasicFountainScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Render() override;
	void Update(float dt) override;
};