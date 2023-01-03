#pragma once

#include "../renderer/renderer.h"
#include "../camera.h"
#include "../../scene.h"
#include "../light.h"

#include "../Shapes/cube.h"
#include "../gui.h"

class SplineGUI : public GUI
{
	//**WHAT IF WE WANT MULTIPLE IMGUI WINDOWS?**
	void CreateWindow()
	{

		ImGui::Begin(" Curves");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
};



class CurveTessellationScene : public Scene
{
public:
	GLFWwindow& m_window;

	GLShader m_shader;
	GLShader m_cube_shader;

	CubeMesh m_cube;

	unsigned int VAO;
	unsigned int VBO;

	SplineGUI m_gui;

	std::shared_ptr<VertexBuffer> m_VBO;
	std::shared_ptr<VertexArray> m_VAO;
	std::shared_ptr<IndexBuffer> m_IBO;

public:
	CurveTessellationScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Update(float dt) override;
	void Render() override;
};