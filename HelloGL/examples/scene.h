 #pragma once

#include <memory>
#include "../renderer/renderer.h"
#include "../camera.h"
#include "../cube.h"
#include "../terrain.h"
#include "../quad.h"


class Scene
{
public:
	Camera m_camera;
public:
	virtual ~Scene() = default;
	Scene() = default;
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	Scene(Scene&&) = delete;
	Scene& operator=(Scene&&) = delete;

	virtual void ProcessInput(float dt, float dx, float dy) =0;
	virtual void Update(float dt) =0;
	virtual void Render() =0;

};
