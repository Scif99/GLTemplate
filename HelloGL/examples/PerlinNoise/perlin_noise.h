#pragma once

#include <memory>
#include <vector>

#include "../renderer/renderer.h"
#include "../camera.h"
#include "../scene.h"
#include "../light.h"
#include "../gui.h"
#include "perlin_noise_gui.h"

#include "../Shapes/cube.h"
#include "../Shapes/terrain.h"
#include "../Shapes/2Dquad.h"


class PerlinNoiseScene : public Scene
{
public:
	GLFWwindow& m_window;

	GLShader m_shader;
	//Camera m_camera;
	GLTexture m_water_texture;

	TerrainMesh m_terrain;
	
	PerlinGui m_gui;

public:
	~PerlinNoiseScene() { m_gui.Cleanup(); }
	PerlinNoiseScene(GLFWwindow* window);
	void ProcessInput(float dt, float dx, float dy) override;
	void Update(float dt) override;
	void Render() override;

};