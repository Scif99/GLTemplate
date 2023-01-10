#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <memory>
#include <vector>

#include "renderer/buffer.h"
#include "renderer/vertex_array.h"


class Grid
{
public:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;
    std::shared_ptr<IndexBuffer> m_IBO;

    //Generates a flat terrain in the x-z plane
    //mPathces is the number of patches in each dimension
    Grid(float xHalfExtents, float zHalfExtents, unsigned int mPatches)
    {

        const float Xunit{ 2.f * xHalfExtents / mPatches }; //distance between each vertex in x-direction
        const float Zunit{ 2.f * zHalfExtents / mPatches }; //distance between each vertex in z-direction

        /* Order of vertices can be visualised like below (left->right, up->down)
        *(-1.f,-1.f,0.f)-->...-->(1.f,-1.f,0.f)
        * ...       ->                ...
        * ...       ->                ...
        * ...       ->                ...
        *(1.f,-1.f,0.f)-->...->(1.f,1.f,0.f)
        */

        int xNumVertices = mPatches + 1;
        int zNumVertices = mPatches + 1;
        m_vertices.reserve(8 * xNumVertices * zNumVertices);

        for (int z = 0; z < zNumVertices;++z)
        {
            for (int x = 0; x < xNumVertices;++x)
            {
                float x_coord{ -xHalfExtents + x * Xunit };
                float y_coord{ 0.f };
                float z_coord{ -zHalfExtents + z * Zunit };
                

                //Position
                m_vertices.push_back(x_coord);
                m_vertices.push_back(y_coord);
                m_vertices.push_back(z_coord);

                //Normal
                m_vertices.push_back(0.f);
                m_vertices.push_back(1.f);
                m_vertices.push_back(0.f);

                //Texture Coordinates
                // (-1.f,-1.f,0.f) has texture coordinates (0,1) and (1.f,-1.f,0.f) has texture coordinates (1,1)
                m_vertices.push_back(x * Xunit / (2.f*xHalfExtents));
                m_vertices.push_back(1.f - (z * Zunit / (2.f*zHalfExtents)));

            }
        }

        m_indices.reserve(3* xNumVertices * zNumVertices);
        for (int z = 0;z < zNumVertices - 1;++z)
        {
            for (int x = 0; x < xNumVertices - 1 ;++x)
            {

                // |\
                // | \
                // |__\

                int curr = (z*xNumVertices) + x;                
                m_indices.push_back(curr);                      
                m_indices.push_back(curr  + xNumVertices);      
                m_indices.push_back(curr + xNumVertices + 1);   

                //  ___
                //  \  |
                //   \ |
                //    \|

                m_indices.push_back(curr);
                m_indices.push_back(curr + xNumVertices + 1);
                m_indices.push_back(curr + 1);



            }
        }

        //specify the layout of the data
        BufferLayout layout{ {ShaderDataType::Float3, "Position"}, {ShaderDataType::Float3, "Normal"},{ ShaderDataType::Float2, "TexCoord"} };
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