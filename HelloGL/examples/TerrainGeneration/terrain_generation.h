#pragma once

#include "../renderer/renderer.h"
#include "../camera.h"
#include "../scene.h"
#include "../gui.h"
#include "../Shapes/cube.h"
#include "../Shapes/terrain.h"
#include "../Shapes/2Dquad.h"


class TerrainGUI : public GUI
{
public:
	TerrainGUI(GLFWwindow* window) : GUI{ window } {}

	void CreateWindow() override final
	{

		ImGui::Begin("Perlin Noise");

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
};


class TerrainGenerationScene : public Scene
{
public:
	GLFWwindow& m_window;

	TerrainGUI m_gui;

	//Shaders
	GLShader m_shader;

	//Textures
	GLTexture m_heightmap;

	//Entities
	TerrainMesh m_terrain;

public:
	~TerrainGenerationScene() { m_gui.Cleanup(); }
	TerrainGenerationScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Update(float dt) override;
	void Render() override;

};