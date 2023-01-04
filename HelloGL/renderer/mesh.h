#ifndef MESH_H
#define MESH_H

#include <glm/glm.hpp>

#include <vector>

#include "buffer.h"
#include "gl_wrappers.h"
#include "shader.h"
#include "texture.h"
#include "vertex_array.h"


#include <string>

struct Vertex
{
	glm::vec3 m_position;
	glm::vec3 m_normal;
	glm::vec2 m_tex_coords;
	//tangents
	//bitangents
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

	unsigned int m_VAO;
	unsigned int m_VBO;
	unsigned int m_IBO;


public:
	~Mesh() = default;
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<ModelTexture>& textures);

	void Draw(const GLShader& shader);
};




#endif // !MESH_H

