#include "fountain.h"
#include <algorithm>

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <numeric>

//Returns a random float in [low,high]
static float GenerateFloat(float low, float high)
{
    assert(low <= high);
    return glm::mix(low, high, static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

BasicFountainScene::BasicFountainScene(GLFWwindow* window)
:   m_window{*window},
    m_quad_shader{"examples/Particles/9.1ParticleFountain/ParticleShader.vert", "examples/Particles/9.1ParticleFountain/ParticleShader.frag" },
    m_quad_texture{"assets/textures/awesomeface.png", false}
    
{
    m_camera.Reset(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
    //glPointSize(10.f); //Point size is computed in shader as a function of distance from the camera!
    srand(static_cast <unsigned> (time(0)));

    //Fill buffer
    constexpr float rate{ 0.1f };
    float startTime{ 0.f };

    for (int i = 0; i < NUM_PARTICLES;++i)
    {
        //First attribute is initial velocity vector
        // Pick the direction of the velocity using polar coordinates
        float theta = GenerateFloat(0.f, glm::pi<float>() / 6.f);
        float phi = GenerateFloat(0.f, 2 * glm::pi<float>());
        glm::vec3 dir{
            std::sinf(theta)* std::cosf(phi),
            std::cosf(theta),
            std::sinf(theta)* std::sinf(phi)
        };

        // Scale to set the magnitude of the velocity (speed)
        float speed = GenerateFloat(1.25f, 1.5f);
        glm::vec3 velocity{ speed * dir };

        unsigned int curr = 4 * i;
        m_data[curr] = velocity.x;
        m_data[curr + 1] = velocity.y;
        m_data[curr + 2] = velocity.z;

        //The second attribute is the start time
        m_data[curr + 3] = i*rate;
    }

    std::array<unsigned int, NUM_PARTICLES> indices;
    std::iota(indices.begin(), indices.end(), 0);


    BufferLayout layout{ {ShaderDataType::Float3, "InitialVelocity"}, {ShaderDataType::Float, "StartTime"} };
    m_VBO = std::make_shared<VertexBuffer>(m_data);
    m_VBO->Bind();
    m_VBO->SetLayout(layout);

    m_IBO = std::make_shared<IndexBuffer>(indices);

    m_VAO = std::make_shared<VertexArray>();
    m_VAO->AddVertexBuffer(m_VBO);
    m_VAO->SetIndexBuffer(m_IBO);

}

void BasicFountainScene::ProcessInput(float dt, float dx, float dy)
{
    m_camera.ProcessKeyboardInput(&m_window, dt);
    m_camera.ProcessMouseInput(&m_window, dx, dy);

}

void BasicFountainScene::Update(float dt)
{
    m_camera.Update();
}

void BasicFountainScene::Render()
{


    //Clear Buffer
    glClearColor(0.1f, 0.1f, 0.1f, 1.f); //state-setting
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT); //state-using
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_PROGRAM_POINT_SIZE);


    m_quad_shader.Use();
    m_quad_texture.Bind();
    
    //Set uniforms
    //Projection & view don't change per object
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = m_camera.GetView();
    glm::mat4 model = glm::mat4(1.f);

    m_quad_shader.SetMat4("u_Projection", projection);
    m_quad_shader.SetMat4("u_View", view);
    m_quad_shader.SetMat4("u_Model", model);


    float time = (float)glfwGetTime();
    m_quad_shader.SetFloat("u_Time", time);
    m_quad_shader.SetFloat("u_ParticleLifetime", 15.f);


    m_VAO->Bind();
    glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);
    m_VAO->Unbind();
}