#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glad/glad.h>
#include <memory>

#include "buffer.h"
#include "gl_wrappers.h"

class VertexArray
{
private:
	GLID m_renderer_ID;
	std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
	std::shared_ptr<IndexBuffer> m_index_buffer;

	int num_attributes{ 0 }; //The total number of vertex attributes over all the associated VBOs

public:
	VertexArray() { glGenVertexArrays(1, &m_renderer_ID); }
	~VertexArray(){ glDeleteVertexArrays(1, &m_renderer_ID); }
	VertexArray(const VertexArray& other) = default;
	VertexArray& operator=(const VertexArray& other) = default;
	VertexArray(VertexArray&& other) = default;
	VertexArray& operator=(VertexArray&& other) = default;

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vbo, int divisor = 0); //contains optional argument for instanced attributes
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& ibo);

	const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const{ return m_vertex_buffers; }
	const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const{ return m_index_buffer; }

	void Bind() const;
	void Unbind() const;
};

#endif // !VERTEX_ARRAY_H
