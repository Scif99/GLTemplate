#pragma once


#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <vector>

class Widget
{
public:
	std::string m_name; //A name for the widget


};

//What if slider is over ints?
//What if i want a slider of morre than 1D? (e.g. a slider for 3d coordinates)

class Slider : Widget
{
	inline static float f{ 0.f };

	float m_min;
	float m_max;

public:

	Slider(float min, float max)
		:m_min{ min }, m_max{ max }
	{
		ImGui::SliderFloat("float", &f, m_min, m_max);
	}

	float& GetValue() const
	{
		return f;
	}

};



//A class for a ImGui slider
class GUI
{

public:
	std::vector<Widget> m_widgets;

public:
	GUI(GLFWwindow* window)
	{
		// Initialize ImGUI
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}
	~GUI() {};

	void Cleanup()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void CreateFrame()
	{
		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}


	//**WHAT IF WE WANT MULTIPLE IMGUI WINDOWS?**
	void CreateWindow()
	{

		ImGui::Begin("Hello, world!");

		//Draw widgets

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();


	}

	void Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

};





//Event pattern?

