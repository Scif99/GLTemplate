#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../renderer/renderer.h"


/*
- Note that a terrainMesh with 2 vertices in each dimension is equivalent to a quad.
- Also note that the mesh is also normalised such that each to lie in [-1,1]
(scaling is done in application?)
*/

/*
TO-DO : Use GL_TRIANGLE_STRIP?
*/

class TerrainMesh
{
public:
    std::shared_ptr<VertexArray> m_VAO;
    std::shared_ptr<VertexBuffer> m_VBO;
    std::shared_ptr<IndexBuffer> m_IBO;

    
    //construct with a specified number of vertices in each 
    TerrainMesh(int xVert, int zVert)
    {

        const float Xunit{ 2.f/(xVert -1)}; //distance between each vertex in x-direction
        const float Zunit{ 2.f / (zVert - 1) };//distance between each vertex in z-direction

        /* Order of vertices can be visualised like below (left->right, up->down)
        *(-1.f,-1.f,0.f)-->...-->(1.f,-1.f,0.f)
        * ...       ->                ...
        * ...       ->                ...
        * ...       ->                ...
        *(1.f,-1.f,0.f)-->...->(1.f,1.f,0.f)
        */

        std::vector<float> vertices;
        vertices.reserve(8* xVert * zVert);

        for (int z = 0; z < zVert;++z)
        {
            for (int x = 0; x < xVert;++x)
            {
                float x_coord{-1.f + x*Xunit};
                float z_coord{-1.f + z*Zunit};
                float y_coord{0.f};

                //Position
                vertices.push_back(x_coord);
                vertices.push_back(y_coord);
                vertices.push_back(z_coord);

                //Normal
                vertices.push_back(0.f);
                vertices.push_back(1.f);
                vertices.push_back(0.f);

                //Texture Coordinates
                // (-1.f,-1.f,0.f) is top left -> (1.f,-1.f,-0.f) is top right
                vertices.push_back(x*Xunit/2.f);
                vertices.push_back(1.f - (z*Zunit / 2.f));

            }
        }
        //Next generate indices 
        std::vector<unsigned int> indices;
        indices.reserve(xVert * zVert*3);
        for (int z = 0;z < zVert-1;++z)
        {
            for (int x = 1;x < zVert;++x)
            {
                int curr = zVert * z + x;
                indices.push_back(curr);
                indices.push_back(curr-1);
                indices.push_back(curr + xVert - 1);

                indices.push_back(curr);
                indices.push_back(curr + xVert - 1);
                indices.push_back(curr + xVert);

            }
        }

        //specify the layout of the data
        BufferLayout layout({ ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2});
        //Generate VBO, attach layout
        m_VBO = std::make_shared<VertexBuffer>(vertices);
        m_VBO->SetLayout(layout);
        m_IBO = std::make_shared<IndexBuffer>(indices);
        m_VAO = std::make_shared<VertexArray>();

        //Configure VAO
        m_VAO->Bind();
        m_VAO->AddVertexBuffer(m_VBO);
        m_VAO->SetIndexBuffer(m_IBO);
        m_VAO->Unbind();
        m_VBO->Unbind();
    }

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

            Then we fill the vertices in major order
        */

        std::vector<float> vertices;

        for (unsigned x = 0; x <= rez - 1; x++) //x-dim
        {
            for (unsigned z = 0; z <= rez - 1; z++) //z-dim
            {
                vertices.push_back(-width / 2.0f + x*xUnit); // v.x
                vertices.push_back(0.0f); // v.y
                vertices.push_back(-height / 2.0f + z*zUnit); // v.z
                vertices.push_back(x / (float)rez); // u
                vertices.push_back(z / (float)rez); // v
            }
        }

        std::vector<unsigned int> indices;
        indices.reserve(rez * rez* 3);
        for (int x = 0; x < rez - 1; ++x)
        {
            for (int z = 0 ; z < rez - 1; ++z)
            {
                //At each iteration we add a patch worth of indices.
                //Edges are described using the same visual as above
                int top_left = rez * x + z;
                indices.push_back(top_left);
                indices.push_back(top_left + rez); //top right
                indices.push_back(top_left +1); //bottom left
                indices.push_back(top_left + rez + 1); //bottom right
            }
        }


        //specify the layout of the data
        BufferLayout layout({ ShaderDataType::Float3, ShaderDataType::Float2 });

        //Generate VBO, attach layout
        m_VBO = std::make_shared<VertexBuffer>(vertices);
        m_VBO->SetLayout(layout);
       m_IBO = std::make_shared<IndexBuffer>(indices);
        m_VAO = std::make_shared<VertexArray>();

        //Configure VAO
        m_VAO->Bind();
        m_VAO->AddVertexBuffer(m_VBO);
        m_VAO->SetIndexBuffer(m_IBO);
        m_VAO->Unbind();
        m_VBO->Unbind();

    }

    void Draw()
    {
        m_VAO->Bind();
        glDrawElements(GL_TRIANGLES, m_IBO->Count(), GL_UNSIGNED_INT, 0);
        m_VAO->Unbind();
    }
    private:
        //GenerateVertices(int xVert, int zVert);
        //GenerateIndices(
};

