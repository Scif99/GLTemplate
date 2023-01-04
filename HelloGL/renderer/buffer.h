#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <cassert>

#include "gl_wrappers.h"

/*An API-agnostic data type for buffer elements*/
static enum class ShaderDataType
{
	None = 0, Float, Float2, Float3, Float4
};

static unsigned int ShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Float: return 4;
		case ShaderDataType::Float2: return 2*4;
		case ShaderDataType::Float3: return 3*4;
		case ShaderDataType::Float4: return 4*4;
	}
	assert(true && "UNKNOWN SHADER DATA TYPE");
	return 0;
}


/*
- A BufferElement is essentially a vertex attribute
- For example, position, texture coordinates etc...
- It also stores the size (in bytes) of the attribute 
- 
*/
struct BufferElement
{
	//std::string m_name;
	ShaderDataType m_type{ShaderDataType::None};
	unsigned int m_size;
	unsigned int m_offset;

	BufferElement(ShaderDataType type)//, const std::string& name)
		: /*m_name{name},*/ m_type{type}, m_size{ShaderDataTypeSize(type)}, m_offset{0}
	{}

	unsigned int GetcomponentCount() const
	{
		switch (m_type)
		{
			case ShaderDataType::Float:  return 1;
			case ShaderDataType::Float2:  return 2;
			case ShaderDataType::Float3:  return 3;
			case ShaderDataType::Float4:  return 4;
		}
	}
};

/*
* A BufferLayout is a container for BufferElements that stores information such as the stride and offset
* We can't just use a vector of BufferElements because, in order to know the stride, and the offset of an attribute,
* we need to know about other elements
*/
class BufferLayout
{
public:
	std::vector<BufferElement> m_elements;
	unsigned int m_stride{ 0 };

	BufferLayout() = default;

	BufferLayout(const std::vector<BufferElement>& elements)
		:m_elements{ elements } 
	{
		CalculateOffsetsAndStride();
	}

	auto begin() const { return m_elements.begin(); }
	auto begin() { return m_elements.begin(); }

	auto end() const { return m_elements.end(); }
	auto end() { return m_elements.end(); }


private:
	void CalculateOffsetsAndStride()
	{
		m_stride = 0;
		for (auto& e : m_elements)
		{
			e.m_offset = m_stride;
			m_stride += e.m_size;
		}
	}
};


class VertexBuffer
{
private:
	GLID m_renderer_ID;
	BufferLayout m_layout;
public:
	//default constructor for dynamic?
	~VertexBuffer() { glDeleteBuffers(1, &m_renderer_ID); };
	VertexBuffer() = default;
	VertexBuffer(const VertexBuffer& other) = default;
	VertexBuffer& operator=(const VertexBuffer& other) = default;
	VertexBuffer(VertexBuffer&& other) = default;
	VertexBuffer& operator=(VertexBuffer&& other) = default;

	VertexBuffer(const glm::vec2 vertices[], unsigned int size);
	VertexBuffer(const float vertices[], unsigned int size);
	VertexBuffer(const std::vector<float>& vertices); //overload for meshes

	void Bind() const;
	void Unbind() const;

	const BufferLayout& GetLayout() const { return m_layout; }
	void SetLayout(const BufferLayout& layout) { m_layout = layout; }
};


//----------------
//Index Buffer
//-----------------------

class IndexBuffer
{
private:
	GLID m_renderer_ID;
	unsigned int m_count;
public:
	~IndexBuffer() { glDeleteBuffers(1, &m_renderer_ID); };
	IndexBuffer() = default;
	IndexBuffer(const IndexBuffer& other) = default;
	IndexBuffer& operator=(const IndexBuffer& other) = default;
	IndexBuffer(IndexBuffer&& other) = default;
	IndexBuffer& operator=(IndexBuffer&& other) = default;

	IndexBuffer(const unsigned int indices[], unsigned int size); //size vs count...
	IndexBuffer(const std::vector<unsigned int>& indices); //size vs count...

	const unsigned int Count() const { return m_count; }
	void Bind() const;
	void Unbind() const;

};


#endif // !VERTEX_BUFFER_H