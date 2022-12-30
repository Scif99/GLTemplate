#pragma once

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
	GLShader m_shader;

	std::shared_ptr<VertexArray> m_VAO;
	std::shared_ptr<VertexBuffer> m_VBO;
	std::shared_ptr<VertexBuffer> m_InstanceVBO;

	std::shared_ptr<IndexBuffer> m_IBO;

	glm::vec2 m_translations[100];



public:
	InstancingScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Render() override;
	void Update(float dt) override;
};