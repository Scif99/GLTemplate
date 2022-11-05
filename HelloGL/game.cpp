#include "game.h"

Game::Game(unsigned int width, unsigned int height)
	: m_state{ GameState::GAME_ACTIVE }, m_keys(), m_width{ width }, m_height{ height }
{

}

void Game::init()
{
    // load shaders
    ResourceManager::LoadShader("shaders/2DSpriteShader.vs", "shaders/2DSpriteShader.fs", "sprite"); //add shader to library
    
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_width),
        static_cast<float>(m_height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite")->Use();
    ResourceManager::GetShader("sprite")->SetInt("image", 0);
    ResourceManager::GetShader("sprite")->SetMat4("projection", projection); //projection only needs to be set once

    // set render-specific controls
    m_renderer = std::make_unique<SpriteRenderer>(ResourceManager::GetShader("sprite"));
    // load textures
    ResourceManager::LoadTexture("assets/textures/awesomeface.png", true, "face"); //add texture to library
    // ResourceManager::LoadTexture(255,0,0, "Red");

}

Game::~Game()
{


}


void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{
    m_renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f);
}