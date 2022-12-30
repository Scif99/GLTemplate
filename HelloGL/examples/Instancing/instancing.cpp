#include "instancing.h"


InstancingScene::InstancingScene(GLFWwindow* window)
:   m_window{*window},
    m_shader{"examples/Instancing/2DQuadShader.vs", "examples/Instancing/2DQuadShader.fs" }

{

    float vertices[] = {
        // positions     // colors
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };

    unsigned int indices[] = {
        0,2,1,
        0,1,3
    };

    int index = 0;
    float offset = 0.1f;
    for (int y = -10; y < 10; y += 2)
    {
        for (int x = -10; x < 10; x += 2)
        {
            glm::vec2 translation;
            translation.x = (float)x / 10.0f + offset;
            translation.y = (float)y / 10.0f + offset;
            m_translations[index++] = translation;
        }
    }

    //Create VBO for the instanced attribute
    BufferLayout instance_layout({ ShaderDataType::Float2});
    m_InstanceVBO = std::make_shared<VertexBuffer>(m_translations, sizeof(glm::vec2) * 100);
    m_InstanceVBO->SetLayout(instance_layout);




    //specify the layout of the data
    BufferLayout layout({ ShaderDataType::Float2, ShaderDataType::Float3 });
    //Generate VBO, attach layout
    m_VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    m_VBO->SetLayout(layout);
    m_IBO = std::make_shared<IndexBuffer>(indices, sizeof(indices));

    //Configure VAO
    //Note that the VBO with the instanced attribute is separate.
    m_VAO = std::make_shared<VertexArray>();
    m_VAO->Bind();
    m_VAO->AddVertexBuffer(m_VBO);
    m_VAO->AddVertexBuffer(m_InstanceVBO, 1); //The second argument specifies the number of instances before the attribute is updated.
    m_VAO->SetIndexBuffer(m_IBO);
    m_VAO->Unbind();
    m_VBO->Unbind();

   
}

void InstancingScene::ProcessInput(float dt, float dx, float dy)
{
    //m_camera.ProcessKeyboardInput(&m_window, dt);
    //m_camera.ProcessMouseInput(&m_window, dx, dy);
}

void InstancingScene::Update(float dt)
{
    //m_camera.Update();
    for (int i = 0;i < 100;++i)
    {
        m_translations[i].x += 0.1f;
    }

}

void InstancingScene::Render()
{
    //Clear Buffer
    glClearColor(0.1f, 0.1f, 0.1f, 1.f); //state-setting
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //state-using
    glEnable(GL_DEPTH_TEST);

    float t = glfwGetTime();
    m_shader.SetFloat("t", t);

    m_shader.Use();
    m_VAO->Bind();
    glDrawElementsInstanced(GL_TRIANGLES, m_IBO->Count(), GL_UNSIGNED_INT, 0, 100);
    m_VAO->Unbind();


}