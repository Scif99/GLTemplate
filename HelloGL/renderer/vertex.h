#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



struct Vertex
{
	glm::vec3 m_position;
	glm::vec3 m_normal;
	glm::vec2 m_tex_coords;

	// Layout() const { return  { ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 }; }
	//tangents
	//bitangents


};