#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>

#include <vector>

#include "buffer.h"
#include "gl_wrappers.h"
#include "shader.h"
#include "texture.h"
#include "vertex_array.h"

#include <concepts>
#include <string>

/*
A VertexAttribute is something like a position, normal or texture coordinate 
*/


struct VertexAttribute
{
	ShaderDataType m_type;
};

struct GLVertex
{
	std::vector<VertexAttribute> m_attributes;
};


struct ModelTexture
{
	unsigned int id;
	std::string type;
	std::string path;
};



class Mesh
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<ModelTexture> m_textures;

	std::shared_ptr<VertexArray> m_VAO;
	std::shared_ptr<VertexBuffer> m_VBO;
	std::shared_ptr<IndexBuffer> m_IBO;


public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<ModelTexture>& textures);

	void Draw(const GLShader& shader);
};




#endif // !MESH_H

