#pragma once


#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <string>
#include <vector>


//A class for a ImGui slider
class GUI
{

public:

	virtual ~GUI() {};

	void CreateFrame()
	{
		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}


	//**WHAT IF WE WANT MULTIPLE IMGUI WINDOWS?**
	virtual void CreateWindow() = 0;

	void Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void Cleanup()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

protected:
	GUI(GLFWwindow* window)
	{
		// Initialize ImGUI
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 430");
	}
};





//Event pattern?

