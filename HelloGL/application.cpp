#include "application.h"



Application::Application(unsigned int width, unsigned int height)
	:m_keys(), m_width{ width }, m_height{ height }
{

}

void Application::init()
{
    m_shader = std::make_unique<GLShader>("shaders/3DShader.vs", "shaders/3DShader.fs");
    m_texture = std::make_unique<GLTexture>("assets/textures/container.jpg", false, "wood");
    
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_camera = std::make_unique<Camera>(cameraPos, cameraFront, cameraUp);


    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    //specify the layout of the data
    BufferLayout layout({ ShaderDataType::Float3, ShaderDataType::Float2});

    //Generate VBO, attach layout
    auto VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    VBO->SetLayout(layout);

    m_VAO = std::make_unique<VertexArray>();

    //Configure VAO
    m_VAO->Bind();
    m_VAO->AddVertexBuffer(VBO);
    m_VAO->Unbind();
    VBO->Unbind();
}

Application::~Application()
{


}

void Application::ProcessInput(GLFWwindow* window, float dt, float dx, float dy)
{
    m_camera->ProcessKeyboardInput(window, dt);
    m_camera->ProcessMouseInput(window, dx, dy);

}

void Application::Update(float dt)
{
    m_camera->Update();

}



void Application::Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); //state-setting
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //state-using

    //Bind shader
    m_shader->Use();

    //-----------
    // MVP
    //------------
    
    //Projection
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    m_shader->SetMat4("projection", projection);

    //camera (view)
    m_shader->SetMat4("view", m_camera->getView());

    //Model
    glm::mat4 model = glm::mat4(1.f);
    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    m_shader->SetMat4("model", model);

    //----------
    //Finally draw
    //-------------

    m_texture->Bind();
    m_VAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    //glDrawElements(GL_TRIANGLES, m_VAO.GetIndexBuffer()->Count(), GL_UNSIGNED_INT, 0);
    m_VAO->Unbind();
}
