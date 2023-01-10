#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <vector>

#include "renderer/buffer.h"
#include "renderer/vertex_array.h"

/*
All instances share a VBO, IBO
	- This is why we use a shared_ptr
*/


class CubeMesh
{
public:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;
    std::shared_ptr<IndexBuffer> m_IBO;


    CubeMesh(float xScale, float yScale)
    {
        m_vertices = CubeMesh::GenerateVertices(xScale, yScale);
        m_indices = CubeMesh::GenerateIndices();

        //specify the layout of the data
        BufferLayout layout({ {ShaderDataType::Float3, "Position"}, { ShaderDataType::Float3, "Normal"}, {ShaderDataType::Float2, "TexCoord"}});

        //Generate VBO, attach layout
        m_VBO = std::make_shared<VertexBuffer>(m_vertices);
        m_VBO->SetLayout(layout);
        m_IBO = std::make_shared<IndexBuffer>(m_indices);
        m_VAO = std::make_shared<VertexArray>();

        //Configure VAO
        m_VAO->Bind();
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
    inline static std::vector<float> GenerateVertices(float xScale, float yScale);
    inline static std::vector<unsigned int> GenerateIndices();

    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;

};

//Both functions should use NRVO to elide copies
std::vector<float> CubeMesh::GenerateVertices(float xScale, float yScale)
{
    std::vector<float> vertices{
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
    return vertices;
}

std::vector<unsigned int> CubeMesh::GenerateIndices()
{
    std::vector<unsigned int> indices{
        0,2,1, 0,3,2,
        4,5,6, 4,6,7,
        8,10,11, 8,9, 10,
        12,15,14, 12,14, 13,
        16,18,19, 16,17,18,
        20,23,22, 20,22,21
    };
    return indices;
}