#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderer/renderer.h"


/*
All instances share a VBO, IBO
	- Thus 
*/

class CubeMesh
{
public:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;
    std::shared_ptr<IndexBuffer> m_IBO;


    CubeMesh()
    {
        {
            float vertices[] = {
                //pos                   //normal             //tex
                -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f, 1.0f,
                                     
                -0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,    0.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,   0.0f,  0.0f, 1.0f,    1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,    1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,   0.0f,  0.0f, 1.0f,    0.0f, 1.0f,
                                     
                -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
                                     
                 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f, 1.0f,
                 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f, 1.0f,
                                     
                                     
                -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 0.0f,
                 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 0.0f,
                 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f, 1.0f,
                                     
                -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 0.0f,
                 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 0.0f,
                 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f, 1.0f

            };

            unsigned int indices[] = {
               0,2,1, 0,3,2,
               4,5,6, 4,6,7, 
               8,10,11, 8,9, 10, 
               12,15,14, 12,14, 13,
               16,18,19, 16,17,18,
               20,23,22, 20,22,21
            };

            //specify the layout of the data
            BufferLayout layout({ ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 });

            //Generate VBO, attach layout
            m_VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
            m_VBO->SetLayout(layout);
            m_IBO = std::make_shared<IndexBuffer>(indices, sizeof(indices));
            m_VAO = std::make_shared<VertexArray>();

            //Configure VAO
            m_VAO->Bind();
            m_VAO->AddVertexBuffer(m_VBO);
            m_VAO->SetIndexBuffer(m_IBO);
            m_VAO->Unbind();
            m_VBO->Unbind();
        }
    }
    void Draw()
    {
        m_VAO->Bind();
        glDrawElements(GL_TRIANGLES, m_VAO->GetIndexBuffer()->Count(), GL_UNSIGNED_INT, 0);
        m_VAO->Unbind();
    }
};


class LightCube
{
public:
    std::shared_ptr<CubeMesh> m_mesh;
    glm::vec3 m_position;
    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    inline static glm::vec3 s_default_pos = glm::vec3(1.2f, 1.0f, 2.0f);
    inline static glm::vec3 s_default_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    inline static glm::vec3 s_default_diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    inline static glm::vec3 s_default_specular = glm::vec3(1.0f, 1.0f, 1.0f);
public:
    LightCube(const glm::vec3& pos, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular)
        : m_position{ pos }, m_ambient{ ambient }, m_diffuse{ diffuse }, m_specular{ specular } 
    { 
        m_mesh = std::make_shared<CubeMesh>();
    } 
};

class Container
{
public:
    std::shared_ptr<CubeMesh> m_mesh;

    Container()
    {
        m_mesh = std::make_shared<CubeMesh>();
    }
};


