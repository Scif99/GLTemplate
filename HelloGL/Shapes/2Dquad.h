#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../renderer/renderer.h"

/*
A rectangular Quad
*/
class Quad
{
public:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;
    std::shared_ptr<IndexBuffer> m_IBO;

    
    unsigned int m_instance_count{ 1 };

    Quad(float width, float height)
    {
        m_vertices = Quad::GenerateVertices(width, height);
        m_indices = Quad::GenerateIndices();

        //specify the layout of the data
        BufferLayout layout({ {ShaderDataType::Float3, "Position"}, {ShaderDataType::Float2, "TextureCoord"}});

        //Generate VBO/IVO, attach layout
        m_VBO = std::make_shared<VertexBuffer>(m_vertices);
        m_VBO->SetLayout(layout);
        m_IBO = std::make_shared<IndexBuffer>(m_indices);

        //Configure VAO
        m_VAO = std::make_shared<VertexArray>();
        m_VAO->AddVertexBuffer(m_VBO);
        m_VAO->SetIndexBuffer(m_IBO);
        m_VAO->Unbind();
        m_VBO->Unbind();

    }

    void Draw(GLPrimitive primitive)
    {

        m_VAO->Bind();
        glDrawElements(static_cast<std::underlying_type<GLPrimitive>::type>(primitive), m_IBO->Count(), GL_UNSIGNED_INT, 0);
        m_VAO->Unbind();
    } 

private:
    inline static std::vector<float> GenerateVertices(float width, float height);
    inline static std::vector<unsigned int> GenerateIndices();

    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;
};

std::vector<float> Quad::GenerateVertices(float width, float height)
{
    std::vector<float> vertices{
                 // positions                    // texCoords
        -1.0f * width,  1.0f * height, 0.f,     0.0f, 1.0f, //top left
        -1.0f * width, -1.0f * height, 0.f,     0.0f, 0.0f, //bottom left
         1.0f * width, -1.0f * height, 0.f,     1.0f, 0.0f, //bototm right
         1.0f * width,  1.0f * height, 0.f,     1.0f, 1.0f  //top right
    };
    return vertices;
}

std::vector<unsigned int> Quad::GenerateIndices()
{
    std::vector<unsigned int> indices{
        0,1,2,
        0,2,3
    };
    return indices;
}

