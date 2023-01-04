#pragma once

#include "camera.h"
#include "renderer/renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "gui.h"

#include "../Shapes/cube.h"
#include "../Shapes/terrain.h"
#include "../Shapes/2Dquad.h"

#include "examples/scene.h"
#include "examples/postProcessing/post_processing_scene.h"
#include "examples/TerrainGeneration/terrain_generation.h"
#include "examples/Instancing/instancing.h"

#include "examples/Tessellation/Curve/curve_tessellation.h"
#include "examples/Tessellation/Quad/quad_tessellation.h"




class GLWindow
{
public:
	GLFWwindow* m_window{ nullptr};

public:
	~GLWindow() { glfwDestroyWindow(m_window); }
};


class Application
{
public:
	enum class State
	{
		MENU,
		SCENE
	};


public:
	bool m_keys[1024];
	unsigned int m_width, m_height;
	State m_state;
	bool drag{ false }; //Used for mouse dragging...

	std::unique_ptr<Scene> m_scene;

	////Window/gui stuff
	GLFWwindow* m_window{nullptr}; //TODO figure out how to use smart pointers...
	std::unique_ptr<GUI> m_gui;


	Application(unsigned int width, unsigned int height);
	~Application() { glfwDestroyWindow(m_window); };

	void init(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy);
	void Update(float dt);
	void Render();
	 
	//Ensure that we cleanup anything that relies on glfw before glfw itself gets cleaned up
	void Cleanup();

};