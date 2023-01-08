#include "buffer.h"

//---------------------
//Vertex Buffer
//--------------------------
VertexBuffer::VertexBuffer(std::span<float> vertices)
{
	glGenBuffers(1, &m_renderer_ID.m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID.m_ID); //'How do we want to use this memory?'
	glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), vertices.data(), GL_STATIC_DRAW); //copy data into our buffer
}

//overload for meshes
VertexBuffer::VertexBuffer(const std::vector<float>& vertices)
{
	glGenBuffers(1, &m_renderer_ID.m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID.m_ID); //'How do we want to use this memory?'
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW); //copy data into our buffer
}

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices)
{
	glGenBuffers(1, &m_renderer_ID.m_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_renderer_ID.m_ID); //'How do we want to use this memory?'
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); //copy data into our buffer
}


//------------------------
//INDEX BUFFER
//-----------------------

IndexBuffer::IndexBuffer(std::span<unsigned int> indices)
	:m_count{indices.size()}
{
	glGenBuffers(1, &m_renderer_ID.m_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_ID.m_ID); //'How do we want to use this memory?'
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), indices.data(), GL_STATIC_DRAW); //copy data into our buffer
}

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices)
	:m_count{ (unsigned int)indices.size()}
{
	glGenBuffers(1, &m_renderer_ID.m_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_ID.m_ID); //'How do we want to use this memory?'
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW); //copy data into our buffer
}
