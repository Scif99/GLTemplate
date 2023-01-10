#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <memory>
#include <vector>

#include "renderer/buffer.h"
#include "renderer/vertex_array.h"



/*
- Note that a terrainMesh with 2 vertices in each dimension is equivalent to a quad.
- Also note that the mesh is also normalised such that each to lie in [-1,1]
(scaling is done in application?)
*/




class TerrainMesh
{
public:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;
    std::shared_ptr<IndexBuffer> m_IBO;

    TerrainMesh(const GLTexture& heightmap)
    {
        int width = heightmap.m_width;
        int height = heightmap.m_height;

        unsigned int rez = 20;
        const float xUnit = width / (float)rez;  //x-distance between vertices
        const float zUnit = height / (float)rez; //z-distance between vertices

        /*
        Imagine looking down from the y-axis like below
            
            -z
            ^
            |
            |
            |
            |____________> x

            From this viewpoint we are filling the vertices in column-major order
        */

        m_vertices.reserve(8 * rez * rez);
        for (unsigned x = 0; x <= rez - 1; x++) //x-dim
        {
            for (unsigned z = 0; z <= rez - 1; z++) //z-dim
            {
                m_vertices.push_back(-width / 2.0f + x*xUnit); // v.x
                m_vertices.push_back(0.0f); // v.y
                m_vertices.push_back(-height / 2.0f + z*zUnit); // v.z
                m_vertices.push_back(x / (float)rez); // u
                m_vertices.push_back(z / (float)rez); // v
            }
        }

        m_indices.reserve(rez * rez* 3);
        for (int x = 0; x < rez - 1; ++x)
        {
            for (int z = 0 ; z < rez - 1; ++z)
            {
                //At each iteration we add a patch worth of indices.
                //Edges are described using the same visual as above
                int top_left = rez * x + z;
                m_indices.push_back(top_left);
                m_indices.push_back(top_left + rez); //top right
                m_indices.push_back(top_left +1); //bottom left
                m_indices.push_back(top_left + rez + 1); //bottom right
            }
        }


        //specify the layout of the data
        BufferLayout layout{ {ShaderDataType::Float3, "Position"}, { ShaderDataType::Float2, "TexCoord"} };

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
    std::vector<float> m_vertices;
    std::vector<unsigned int> m_indices;
};

