#include "vertex_array.h"

#include <iostream>

void VertexArray::Bind() const
{
	glBindVertexArray(m_renderer_ID.Value());
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo, int divisor /* = 0*/)
{
    assert(vbo->GetLayout().m_elements.size() && "No Layout Has Been Set!");

    glBindVertexArray(m_renderer_ID.Value());
    vbo->Bind();

    //Get 
    int attrib_index = num_attributes;
    const auto& layout = vbo->GetLayout();
    for (const auto& attrib : layout)
    {
        glEnableVertexAttribArray(attrib_index);
        glVertexAttribPointer(attrib_index, attrib.GetcomponentCount(), GL_FLOAT, GL_FALSE, vbo->GetLayout().m_stride, (void*)attrib.m_offset);
        if (divisor != 0)
        {
            assert(divisor > 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glVertexAttribDivisor(attrib_index, divisor); // tell OpenGL this is an instanced vertex attribute.
        }
        ++attrib_index;
    }
    num_attributes = attrib_index; //update total number of attributes in VAO
    m_vertex_buffers.push_back(vbo);
}



void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo)
{
    glBindVertexArray(m_renderer_ID.Value());
    ibo->Bind();
    m_index_buffer = ibo;
}