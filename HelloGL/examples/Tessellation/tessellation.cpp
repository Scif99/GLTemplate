#include "tessellation.h"




TessellationScene::TessellationScene(GLFWwindow* window)
	:   m_window{ *window }, 
		m_shader{ "examples/Tessellation/shader.vert", "examples/Tessellation/shader.frag",
				 "examples/Tessellation/shader.tesc","examples/Tessellation/shader.tese" },
		m_cube_shader{"examples/Tessellation/cubeshader.vert", "examples/Tessellation/cubeShader.frag" }

{
	m_camera.Reset(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
	glPatchParameteri(GL_PATCH_VERTICES, 4); //number of vertices per patch


	float vertices[] = {
	-0.5f,-0.5f, 0.f,
	-0.25f,0.5f, 0.f,
	0.f,-0.5f, 0.f,
	0.25f,0.5f, 0.f
	};

	unsigned int indices[] = {
		0,1,2,3
	};

	//specify the layout of the data
	BufferLayout layout({ ShaderDataType::Float3 });

	//Generate VBO, attach layout
	m_VBO = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
	m_VBO->SetLayout(layout);

	m_IBO = std::make_shared<IndexBuffer>(indices, sizeof(indices));
	m_VAO = std::make_shared<VertexArray>();

	//Configure VAO
	m_VAO->Bind();
	m_VAO->AddVertexBuffer(m_VBO);
	m_VAO->SetIndexBuffer(m_IBO);
	m_VAO->Unbind();
	m_VBO->Unbind();

}


void TessellationScene::ProcessInput(float dt, float dx, float dy)
{
	m_camera.ProcessKeyboardInput(&m_window, dt);
	m_camera.ProcessMouseInput(&m_window, dx,dy);
}
void TessellationScene::Update(float dt)
{
	m_camera.Update();
	std::cout << m_camera.Position().x << '\n';
}


void TessellationScene::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f); //state-setting
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //state-using
	glEnable(GL_DEPTH_TEST);

	//Projection & view don't change per object
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glm::mat4 view = m_camera.getView();
	glm::mat4 model = glm::mat4(1.f);

	m_shader.Use();

	m_shader.SetMat4("model", model);
	m_shader.SetMat4("view", view);
	m_shader.SetMat4("projection", projection);
	
	m_shader.SetInt("NumSegments", 30);
	m_shader.SetInt("NumStrips", 1);


	//Bind shader, pass uniforms
	m_VAO->Bind();
	glDrawElements(GL_PATCHES, m_IBO->Count(), GL_UNSIGNED_INT, 0);
	m_VAO->Unbind();

	//Also draw some shapes at control points

	m_cube_shader.Use();
	m_cube_shader.SetMat4("view", view);
	m_cube_shader.SetMat4("projection", projection);

	std::vector<glm::vec3> translations{ 
		{ -0.5f,-0.5f, 0.f},
		{-0.25f,0.5f, 0.f},
		{0.f,-0.5f, 0.f},
		{0.25f,0.5f, 0.f} 
	};

	for (int i =0; i<translations.size();++i)
	{
		glm::mat4 cube_model = glm::mat4(1.f);
		cube_model = glm::translate(cube_model, translations[i]);
		cube_model = glm::scale(cube_model, glm::vec3(0.05f, 0.05f, 0.05f));

		m_cube_shader.SetMat4("model", cube_model);
		m_cube.Draw();

	}
}