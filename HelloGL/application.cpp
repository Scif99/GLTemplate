#include "application.h"

Application::Application(unsigned int width, unsigned int height)
	:m_keys(), m_width{ width }, m_height{ height }
{

}

void Application::init(GLFWwindow* window)
{
    //Load scene
    //(scene can have stall-allocated members rather than pointers everywhere)
    m_scene = std::make_unique<PostProcessingScene>(window);
}


void Application::ProcessInput(float dt, float dx, float dy)
{
    m_scene->ProcessInput(dt, dx, dy);

}

void Application::Update(float dt)
{
    m_scene->Update(dt);
}

void Application::Render()
{
    m_scene->Render();
}

void Application::Cleanup()
{
}
