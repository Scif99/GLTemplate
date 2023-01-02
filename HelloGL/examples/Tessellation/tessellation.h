#pragma once

#include "../renderer/renderer.h"
#include "../camera.h"
#include "../scene.h"
#include "../light.h"

#include "../Shapes/cube.h"
#include "../Shapes/terrain.h"
#include "../Shapes/2Dquad.h"

class TessellationScene : public Scene
{
public:
	GLFWwindow& m_window;

	GLShader m_shader;
	GLShader m_cube_shader;
	//Camera m_camera;

	CubeMesh m_cube;

	std::shared_ptr<VertexBuffer> m_VBO;
	std::shared_ptr<VertexArray> m_VAO;
	std::shared_ptr<IndexBuffer> m_IBO;

public:
	TessellationScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Update(float dt) override;
	void Render() override;
};