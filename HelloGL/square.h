#pragma once
#include "renderer/buffer.h"
#include "renderer/texture.h"
#include "renderer/shader.h"
#include "renderer/vertex_array.h"


class Square
{
private:
	VertexArray m_VAO;
	std::shared_ptr<VertexBuffer> m_VBO;
	std::shared_ptr<GLShader> m_shader;

public:

	Square();


};

Square::Square()
{
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f, //bottom left
        1.0f, 0.0f, 1.0f, 0.0f, //top right
        0.0f, 0.0f, 0.0f, 0.0f, //top left

        0.0f, 1.0f, 0.0f, 1.0f, //bottom left
        1.0f, 1.0f, 1.0f, 1.0f, //bottom right
        1.0f, 0.0f, 1.0f, 0.0f  //top right
    };

    //specify the layout of the data
    BufferLayout layout({ ShaderDataType::Float2, ShaderDataType::Float2 });

    //Generate VBO, attach layout
    auto VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    VBO->SetLayout(layout);

    //Bind VAO, add attribute config
    m_VAO.Bind();
    m_VAO.AddVertexBuffer(VBO);

    m_VAO.Unbind();

}