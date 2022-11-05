#pragma once
#include "resource_manager.h"
#include "sprite_renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Game
{
public:
	enum class GameState
	{
		GAME_ACTIVE,
		GAME_MENU,
		GAME_WIN
	};

public:
	GameState m_state;
	bool m_keys[1024];
	unsigned int m_width, m_height;

	std::unique_ptr<SpriteRenderer> m_renderer;

	Game(unsigned int width, unsigned int height);
	~Game(); 

	void init();
	void ProcessInput(float dt);
	void Update(float dt);
	void Render();
};