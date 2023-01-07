#include "mesh.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<ModelTexture>& textures)
	: m_vertices{ vertices }, m_indices{ indices }, m_textures{ textures }
{

	//specify the layout of the data
	BufferLayout layout{ {ShaderDataType::Float3, "Position"}, {ShaderDataType::Float3, "Normal"},{ ShaderDataType::Float2, "TexCoord"} };
	//Generate VBO, attach layout
	m_VBO = std::make_shared<VertexBuffer>(vertices);
	m_VBO->SetLayout(layout);
	m_IBO = std::make_unique<IndexBuffer>(indices);
	m_VAO = std::make_unique<VertexArray>();

	//Configure VAO
	m_VAO->Bind();
	m_VAO->AddVertexBuffer(m_VBO);
	m_VAO->SetIndexBuffer(m_IBO);
	m_VAO->Unbind();
	m_VBO->Unbind();
}


void Mesh::Draw(const GLShader& shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	//need to bind all the necessary texture units
	for (unsigned int i = 0; i < m_textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = m_textures[i].type;

		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++);
		else
		{
			std::cerr << "Error: Texture format unrecognised. ";
		}
		shader.SetInt(("material." + name + number).c_str(), i); //In this implementation we stored our textures in a material struct (see frag shader)
		glBindTexture(GL_TEXTURE_2D, m_textures[i].id);

	}
	m_VAO->Bind();
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	m_VAO->Unbind();

	glActiveTexture(GL_TEXTURE0);
}