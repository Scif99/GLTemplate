#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>

#include "camera.h"
#include "gui.h"

#include "scene.h"
#include "examples/postProcessing/post_processing_scene.h"
#include "examples/TerrainGeneration/terrain_generation.h"
#include "examples/Tessellation/Curve/curve_tessellation.h"
#include "examples/Tessellation/Quad/quad_tessellation.h"

//Particle Scenes
#include "examples/Particles/9.1ParticleFountain/fountain.h"


class Application
{

public:
	Application(unsigned int width, unsigned int height);
	~Application() { glfwDestroyWindow(m_window); };
	//Copy/Moves?

	void init(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy);
	void Update(float dt);
	void Render();
	 
	//Ensure that we cleanup anything that relies on glfw before glfw itself gets cleaned up
	void Cleanup();

public:
	bool m_keys[1024];
	unsigned int m_width, m_height;
	bool drag{ false }; //Used for mouse dragging...

	std::unique_ptr<Scene> m_scene;

	////Window/gui stuff
	GLFWwindow* m_window{ nullptr }; //TODO figure out how to use smart pointers...
};


class MenuGUI : public GUI
{
public:
	MenuGUI(GLFWwindow* window) : GUI{ window } {}

	void CreateWindow() override final
	{

		ImGui::Begin(" Quads");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

};


class MenuScene : public Scene
{
private:
	GLFWwindow& m_window;
	MenuGUI m_gui;

public:
	MenuScene(GLFWwindow* window) : m_window{ *window }, m_gui{ window } {}

	void ProcessInput(float dt, float dx, float dy) override
	{
		m_camera.ProcessKeyboardInput(&m_window, dt);
		m_camera.ProcessMouseInput(&m_window, dx, dy);
	}

	void Update(float dt) override
	{
		m_gui.CreateFrame();
		m_camera.Update();
	}
	void Render() override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		//Configure GUI
		ImGui::Begin("Scene Menu");

		const char* items[] = { "Instancing", "Post Processing (FrameBuffers)", "Terrain Generation", "Tessellation (Curves)", "Tessellation (Quads)" };
		static int item_current = 1;
		ImGui::ListBox("listbox", &item_current, items, IM_ARRAYSIZE(items), 4);
		ImGui::End();

		m_gui.Render();
	}
};