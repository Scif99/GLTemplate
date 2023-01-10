#pragma once

#include "camera.h"
#include "gui.h"
#include "scene.h"

#include "renderer/buffer.h"
#include "renderer/shader.h"
#include "renderer/vertex_array.h"

#include "Shapes/2Dquad.h"

class QuadTessellationGUI : public GUI
{
public:
	QuadTessellationGUI(GLFWwindow* window) : GUI{ window } {}

	void CreateWindow() override final
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
	QuadTessellationGUI m_gui;

	std::shared_ptr<VertexBuffer> m_VBO;
	std::shared_ptr<VertexArray> m_VAO;
	std::shared_ptr<IndexBuffer> m_IBO;

public:
	QuadTessellationScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Update(float dt) override;
	void Render() override;
};