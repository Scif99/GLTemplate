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
    //By default the mesh lies in the x-z plane, with a normal in the +ve y-direction
    TerrainMesh(int xVert, int zVert)
    {

        const float Xunit{ 2.f/(xVert -1)}; //distance between each vertex in x-direction
        const float Zunit{ 2.f / (zVert - 1) };//distance between each vertex in z-direction

        std::vector<float> vertices;
        vertices.reserve(xVert * zVert);
        /* Order of vertices can be visualised like below (left->right, up->down)
        *(-1.f,-1.f,0.f)-->...-->(1.f,-1.f,0.f)
        * ...       ->                ...
        * ...       ->                ...
        * ...       ->                ...
        *(1.f,-1.f,0.f)-->...->(1.f,1.f,0.f)
        */
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

    TerrainMesh(const std::string& heightmap_path)
    {
        // load height map texture
        int width, height, nChannels;
        unsigned char* data = stbi_load(heightmap_path.c_str(),
            &width, &height, &nChannels, 0);

        const float Xunit{ 2.f / (width - 1) }; //distance between each vertex in x-direction
        const float Zunit{ 2.f / (height - 1) };//distance between each vertex in z-direction

        std::vector<float> vertices;
        vertices.reserve(8*width * height); //3(position) + 3(normal) + 2(texture)

        float yScale = 64.0f / 256.0f, yShift = 16.0f;  // apply a scale+shift to the height data
        for (int z = 0; z < height;++z)
        {
            for (int x = 0; x < width;++x)
            {
                float x_coord{ -1.f + x * Xunit };
                float z_coord{ -1.f + z * Zunit };
                unsigned char* texel = data + (x + width * z) * nChannels;
                float y_coord = (float)texel[0];

                ////Position
                //vertices.push_back(x_coord);
                //vertices.push_back((int)y_coord * yScale - yShift);
                //vertices.push_back(z_coord);

                vertices.push_back(-height / 2.0f + z);        // v.x
                vertices.push_back((int)y_coord * yScale - yShift); // v.y
                vertices.push_back(-width / 2.0f + x);        // v.z

                //Normal
                vertices.push_back(0.f);
                vertices.push_back(1.f);
                vertices.push_back(0.f);

                //Texture Coordinates
                // (-1.f,-1.f,0.f) is top left -> (1.f,-1.f,-0.f) is top right
                vertices.push_back(x * Xunit / 2.f);
                vertices.push_back(1.f - (z * Zunit / 2.f));

            }
        }
        stbi_image_free(data);

        std::vector<unsigned int> indices;
        indices.reserve(width * height* 3);
        for (int z = 0;z < height - 1;++z)
        {
            for (int x = 1;x < height;++x)
            {
                //At each iteration we add a quad's (two triangles) worth of indices.
                int curr = width * z + x;
                indices.push_back(curr);
                indices.push_back(curr - 1);
                indices.push_back(curr + width - 1);

                indices.push_back(curr);
                indices.push_back(curr + width - 1);
                indices.push_back(curr + width);

            }
        }

        //specify the layout of the data
        BufferLayout layout({ ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 });

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

