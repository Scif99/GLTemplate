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

	GLShader m_shader;
	GLTexture m_water_texture;
	TerrainMesh m_terrain;
	
	PerlinGui m_gui;

public:
	~TerrainGenerationScene() { m_gui.Cleanup(); }
	TerrainGenerationScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Update(float dt) override;
	void Render() override;

};