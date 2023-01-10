 #pragma once

#include <memory>
#include "../camera.h"
#include "../renderer/gl_wrappers.h"

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
