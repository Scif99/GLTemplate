#include "instancing.h"
#include <algorithm>

#include <ctime>
#include <cstdlib>
#include <cmath>

//Returns a random float in [low,high]
float GenerateFloat(float low, float high)
{
    assert(low <= high);
    return glm::mix(low, high, static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}


InstancingScene::InstancingScene(GLFWwindow* window)
:   m_window{*window},
    m_quad_shader{"examples/Instancing/InstancedQuadShader.vert", "examples/Instancing/InstancedQuadShader.frag" },
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





    //Finally configure VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO); 
    glBufferData(GL_ARRAY_BUFFER, m_data.size() * sizeof(float), m_data.data(), GL_STATIC_DRAW);


    //Configure Layout
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_VERTEX_ARRAY, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void InstancingScene::ProcessInput(float dt, float dx, float dy)
{
    m_camera.ProcessKeyboardInput(&m_window, dt);
    m_camera.ProcessMouseInput(&m_window, dx, dy);

}

void InstancingScene::Update(float dt)
{
    m_camera.Update();
}

void InstancingScene::Render()
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
    glm::mat4 view = m_camera.getView();
    glm::mat4 model = glm::mat4(1.f);

    m_quad_shader.SetMat4("u_Projection", projection);
    m_quad_shader.SetMat4("u_View", view);
    m_quad_shader.SetMat4("u_Model", model);


    float time = (float)glfwGetTime();
    m_quad_shader.SetFloat("u_Time", time);
    m_quad_shader.SetFloat("u_ParticleLifetime", 15.f);


    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, NUM_PARTICLES);
    glBindVertexArray(0);



}