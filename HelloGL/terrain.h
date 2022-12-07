#pragma once


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderer/renderer.h"


/*
All instances share a VBO, IBO
    - Thus
*/

//A terrain mesh is just a square for now


class TerrainMesh
{
public:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;

    TerrainMesh()
    {
        
        float vertices[] = {
            //pos                //normal       //tex
           -0.5f, 0.f,-0.5f,    0.f,1.f,0.f,  0.f,0.f,
            0.5f, 0.f,-0.5f,    0.f,1.f,0.f,  1.f,0.f,
            0.5f, 0.f, 0.5f,    0.f,1.f,0.f,  1.f,1.f,
           -0.5f, 0.f, 0.5f,    0.f,1.f,0.f,  0.f,1.f
        };

        unsigned int indices[] = {
            0,2,1,
            0,3,2
        };

        //specify the layout of the data
        BufferLayout layout({ ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 });

        //Generate VBO, attach layout
        m_VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
        m_VBO->SetLayout(layout);

        auto IBO = std::make_shared<IndexBuffer>(indices, sizeof(indices));

        m_VAO = std::make_shared<VertexArray>();

        //Configure VAO
        m_VAO->Bind();
        m_VAO->AddVertexBuffer(m_VBO);
        m_VAO->SetIndexBuffer(IBO);
        m_VAO->Unbind();
        m_VBO->Unbind();

    }
    void Draw()
    {
        m_VAO->Bind();
        glDrawElements(GL_TRIANGLES, m_VAO->GetIndexBuffer()->Count(), GL_UNSIGNED_INT, 0);
        m_VAO->Unbind();
    }
};


class Terrain
{
public:
    std::shared_ptr<TerrainMesh> m_mesh;
    Terrain()
    {
        m_mesh = std::make_shared<TerrainMesh>();
    }
};
