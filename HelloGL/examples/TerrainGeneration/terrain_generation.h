#pragma once

#include "../renderer/renderer.h"
#include "../camera.h"
#include "../scene.h"
#include "../gui.h"
#include "terrain_generation_gui.h"

#include "../Shapes/cube.h"
#include "../Shapes/terrain.h"
#include "../Shapes/2Dquad.h"



class TerrainGenerationScene : public Scene
{
public:
	GLFWwindow& m_window;

	PerlinGui m_gui;
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