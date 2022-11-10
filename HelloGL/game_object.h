#pragma once

#include <memory>

#include "renderer/buffer.h"
#include "renderer/texture.h"

class GameObject
{
private:
	std::shared_ptr<GLTexture> m_texture;
	glm::vec2 m_position;
	glm::vec2 m_size;
	bool is_destroyed;
public:
	GameObject();


	void init();
	void update(float dt);
	void render(float dt);
};