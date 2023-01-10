#pragma once

#include "camera.h"
#include "gui.h"
#include "scene.h"

#include "renderer/shader.h"
#include "Shapes/cube.h"

class SplineGUI : public GUI
{
public:

	SplineGUI(GLFWwindow* window) : GUI{ window } {}

	void CreateWindow() override final
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

	//VAO/VBO for control points
	unsigned int VAO;
	unsigned int VBO;

	SplineGUI m_gui;

public:
	CurveTessellationScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Update(float dt) override;
	void Render() override;
};




