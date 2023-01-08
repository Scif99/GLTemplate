#include "instancing.h"


InstancingScene::InstancingScene(GLFWwindow* window)
:   m_window{*window},
    m_quad_shader{"examples/Instancing/InstancedQuadShader.vert", "examples/Instancing/InstancedQuadShader.frag" },
    m_quad_texture{"assets/textures/awesomeface.png"},
    m_quad{0.05f, m_translations.size()} //Scale down by 20x
{
    //Store translation vectors for each instance
    int index = 0;
    float offset = 0.1f;
    for (int y = -10; y < 10; y += 2)
    {
        for (int x = -10; x < 10; x += 2)
        {
            m_translations[index++] = (float)x / 10.0f + offset;
            m_translations[index++] = (float)y / 10.0f + offset;
        }
    }

    BufferLayout instanced_layout{ { ShaderDataType::Float2, "Position" } };
    m_InstanceVBO = std::make_shared<VertexBuffer>(m_translations);
    m_InstanceVBO->SetLayout(instanced_layout);

    m_quad.m_VAO->Bind();
    m_quad.m_VAO->AddVertexBuffer(m_InstanceVBO, 1);
    m_quad.m_VAO->Unbind();
  
}

void InstancingScene::ProcessInput(float dt, float dx, float dy)
{

}

void InstancingScene::Update(float dt)
{
    //for (int i = 0;i < 100;++i)
    //{
    //    m_translations[i].x += 0.1f;
    //}

}

void InstancingScene::Render()
{
    //Clear Buffer
    glClearColor(0.1f, 0.1f, 0.1f, 1.f); //state-setting
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //state-using
    glEnable(GL_DEPTH_TEST);

    float t = glfwGetTime();
    m_quad_shader.SetFloat("t", t);

    m_quad_shader.Use();
    m_quad_texture.Bind();
    m_quad.Draw(GLPrimitive::TRIANGLE);

}