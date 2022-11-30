#include "application.h"



Application::Application(unsigned int width, unsigned int height)
	:m_keys(), m_width{ width }, m_height{ height }
{

}

void Application::init()
{
    m_shader = std::make_unique<GLShader>("shaders/3DShader.vs", "shaders/3DShader.fs");
    m_texture = std::make_unique<GLTexture>("assets/textures/container.jpg", false, "wood");

    m_lightsourceshader = std::make_unique<GLShader>("shaders/LightSourceShader.vs", "shaders/LightSourceShader.fs");
    
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_camera = std::make_unique<Camera>(cameraPos, cameraFront, cameraUp);



    float vertices[] = {
        //pos                   //tex      //normal
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  0.0f,  1.0f,  0.0f
    };

    //specify the layout of the data
    BufferLayout layout({ ShaderDataType::Float3, ShaderDataType::Float2, ShaderDataType::Float3 });

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
    glClearColor(0.f, 0.f, 0.f, 0.f); //state-setting
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //state-using

    //Projection & view don't change per object
    glm::mat4 projection =  glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = m_camera->getView();

    glm::vec3 light_color = glm::vec3(1.f, 1.f, 1.f);
   
    glm::vec3 light_pos(1.2f, 1.0f, 2.0f);

    //-------------------
    // WOODEN CONTAINER
    //---------------
    //Bind shader, pass uniforms
    m_shader->Use();
    m_shader->SetMat4("projection", projection);
    m_shader->SetMat4("view", view);
    m_shader->SetVec3("lightColor", light_color);
    m_shader->SetVec3("lightPos", light_pos);
    m_shader->SetVec3("viewPos", m_camera->Position());

    m_shader->SetVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    m_shader->SetVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    m_shader->SetVec3("material.specular",glm::vec3( 0.5f, 0.5f, 0.5f));
    m_shader->SetFloat("material.shininess", 32.0f);

    m_shader->SetVec3("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
    m_shader->SetVec3("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f)); // darken diffuse light a bit
    m_shader->SetVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

    //Model
    glm::mat4 model = glm::mat4(1.f);
    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    m_shader->SetMat4("model", model);

    //draw
    m_texture->Bind();
    m_VAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    //glDrawElements(GL_TRIANGLES, m_VAO.GetIndexBuffer()->Count(), GL_UNSIGNED_INT, 0);
    m_VAO->Unbind();

    //-----------
    //LIGHT SOURCE
    //-------------

    //Configure shader, pass uniforms
    m_lightsourceshader->Use();
    m_lightsourceshader->SetVec3("lightColor", light_color);
    m_lightsourceshader->SetMat4("projection", projection);
    m_lightsourceshader->SetMat4("view", view);

    //Model
    glm::mat4 Lightmodel = glm::mat4(1.f);
    Lightmodel = glm::translate(Lightmodel, light_pos);
    Lightmodel = glm::scale(Lightmodel, glm::vec3(0.2f));
    m_lightsourceshader->SetMat4("model", Lightmodel);

    //Draw
    m_VAO->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    //glDrawElements(GL_TRIANGLES, m_VAO.GetIndexBuffer()->Count(), GL_UNSIGNED_INT, 0);
    m_VAO->Unbind();

}
