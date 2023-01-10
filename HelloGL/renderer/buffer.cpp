#include "buffer.h"
#include <iostream>
//---------------------
//Vertex Buffer
//--------------------------
VertexBuffer::VertexBuffer(std::span<float> vertexAttributes)
{
	glGenBuffers(1, &m_renderer_ID.m_ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, vertexAttributes.size_bytes(), vertexAttributes.data(), GL_STATIC_DRAW); //copy data into our buffer
	Unbind();
}

//overload for meshes
VertexBuffer::VertexBuffer(const std::vector<float>& vertexAttributes)
{
	glGenBuffers(1, &m_renderer_ID.m_ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, vertexAttributes.size() * sizeof(float), &vertexAttributes[0], GL_STATIC_DRAW); //copy data into our buffer
	Unbind();
}

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertexAttributes)
{
	glGenBuffers(1, &m_renderer_ID.m_ID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, vertexAttributes.size() * sizeof(Vertex), &vertexAttributes[0], GL_STATIC_DRAW); //copy data into our buffer
	Unbind();
}

void VertexBuffer::AddAttributes(std::span<float> vertexAttributes)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, vertexAttributes.size_bytes(), vertexAttributes.data(), GL_STATIC_DRAW); //copy data into our buffer
	Unbind();
}

void VertexBuffer::AddAttributes(const std::vector<float>& vertexAttributes)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, vertexAttributes.size() * sizeof(Vertex), &vertexAttributes[0], GL_STATIC_DRAW); //copy data into our buffer
	Unbind();
}

//------------------------
//INDEX BUFFER
//-----------------------

IndexBuffer::IndexBuffer(std::span<unsigned int> indices)
	:m_count{(unsigned int)indices.size()}
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
