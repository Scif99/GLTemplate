#include "application.h"



Application::Application(unsigned int width, unsigned int height)
	:m_keys(), m_width{ width }, m_height{ height }
{

}

void Application::init()
{
    m_container_shader = std::make_unique<GLShader>("shaders/3DShader.vs", "shaders/3DShader.fs");
    m_diffuse_map = std::make_unique<GLTexture>("assets/textures/container2.png", false, "diffuse");
    m_specular_map = std::make_unique<GLTexture>("assets/textures/container2_specular.png", false, "specular");


    m_lightsourceshader = std::make_unique<GLShader>("shaders/LightSourceShader.vs", "shaders/LightSourceShader.fs");

    //set properties of light (doesn't change per frame for now...)
    glm::vec3 light_pos = glm::vec3(1.2f, 1.0f, 2.0f);
    glm::vec3 light_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 light_diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 light_specular = glm::vec3(1.0f, 1.0f, 1.0f);
    m_light = std::make_unique<LightSource>(light_pos, light_ambient, light_diffuse, light_specular);

    //configure camera
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

    unsigned int indices[] = {
        0,1,2, 3,4,5,
        6,7,8, 9,10,11,
        12,13,14, 15,16,17,
        18,19,20, 21,22,23,
        24,25,26, 27,28,29,
        30,31,32, 33,34,35
    };

    //specify the layout of the data
    BufferLayout layout({ ShaderDataType::Float3, ShaderDataType::Float2, ShaderDataType::Float3 });

    //Generate VBO, attach layout
    auto VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    VBO->SetLayout(layout);

    auto IBO = std::make_shared<IndexBuffer>(indices, sizeof(indices));

    m_VAO = std::make_unique<VertexArray>();

    //Configure VAO
    m_VAO->Bind();
    m_VAO->AddVertexBuffer(VBO);
    m_VAO->SetIndexBuffer(IBO);
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

    //-------------------
    // WOODEN CONTAINER
    //---------------
    //Bind shader, pass uniforms
    m_container_shader->Use();
    m_container_shader->SetMat4("projection", projection);
    m_container_shader->SetMat4("view", view);
    m_container_shader->SetVec3("viewPos", m_camera->Position());

    m_container_shader->SetFloat("material.shininess", 64.f);

    //**TODO add a SetMaterial(amb, diff, spec) function?**
    m_container_shader->SetVec3("light.position", m_light->m_position);
    m_container_shader->SetVec3("light.ambient", m_light->m_ambient);
    m_container_shader->SetVec3("light.diffuse", m_light->m_diffuse); // darken diffuse light a bit
    m_container_shader->SetVec3("light.specular", m_light->m_specular);

    //Model
    glm::mat4 model = glm::mat4(1.f);
    m_container_shader->SetMat4("model", model);

    //draw
    m_diffuse_map->Bind(0);
    m_specular_map->Bind(1);
    m_VAO->Bind();
    glDrawElements(GL_TRIANGLES, m_VAO->GetIndexBuffer()->Count(), GL_UNSIGNED_INT, 0);
    m_VAO->Unbind();

    //-----------
    //LIGHT SOURCE
    //-------------

    //Configure shader, pass uniforms
    m_lightsourceshader->Use();
    m_lightsourceshader->SetMat4("projection", projection);
    m_lightsourceshader->SetMat4("view", view);

    //Model
    glm::mat4 Lightmodel = glm::mat4(1.f);
    Lightmodel = glm::translate(Lightmodel, m_light->m_position);
    Lightmodel = glm::scale(Lightmodel, glm::vec3(0.2f));
    m_lightsourceshader->SetMat4("model", Lightmodel);

    //Draw
    m_VAO->Bind();
    glDrawElements(GL_TRIANGLES, m_VAO->GetIndexBuffer()->Count(), GL_UNSIGNED_INT, 0);
    m_VAO->Unbind();

}
