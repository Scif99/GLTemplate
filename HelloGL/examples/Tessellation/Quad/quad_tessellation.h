#pragma once

#include "../renderer/renderer.h"
#include "../camera.h"
#include "../../scene.h"
#include "../light.h"

#include "../Shapes/cube.h"
#include "../Shapes/terrain.h"
#include "../Shapes/2Dquad.h"
#include "../gui.h"

class QuadTessellationGIU : public GUI
{
	//**WHAT IF WE WANT MULTIPLE IMGUI WINDOWS?**
	void CreateWindow()
	{

		ImGui::Begin(" Quads");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
};


class QuadTessellationScene : public Scene
{
public:
	GLFWwindow& m_window;

	GLShader m_shader;
	QuadTessellationGIU m_gui;

	unsigned int VAO, VBO;

public:
	QuadTessellationScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Update(float dt) override;
	void Render() override;
};