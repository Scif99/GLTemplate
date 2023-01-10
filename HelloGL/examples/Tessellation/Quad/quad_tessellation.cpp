#include "quad_tessellation.h"

/*
This scene renders two quads, both of which are tessellated using tessellation shaders
- Note that techincally the shared edge should really have the same tessellation level.

*/

QuadTessellationScene::QuadTessellationScene(GLFWwindow* window)
	: m_window{ *window },
	m_shader{ "examples/Tessellation/Quad/QuadShader.vert", "examples/Tessellation/Quad/QuadShader.frag",
			"examples/Tessellation/Quad/QuadShader.tesc", "examples/Tessellation/Quad/QuadShader.tese" },
	m_gui{ window }

{
	glPatchParameteri(GL_PATCH_VERTICES, 4); //number of vertices per patch
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Wireframe mode


	//1 quad = 1 patch
	float vertices[] = {
		//left column
		- 0.5f, -0.5f,
		-0.5f, 0.5f,
		//mid column
		0.f, -0.5f,
		0.f, 0.5f,
		//right column
		0.5f, -0.5f,
		0.5f, 0.5f
	};

	unsigned int indices[] = {
		//left quad
		0,2,3,1,
		//right quad
		2,4,5,3

	};

	BufferLayout layout{ {ShaderDataType::Float2, "Vertices"}, {ShaderDataType::Float, "Indices"} };
	m_VBO = std::make_shared<VertexBuffer>(vertices);
	m_VBO->SetLayout(layout);

	m_IBO = std::make_shared<IndexBuffer>(indices);

	m_VAO = std::make_shared<VertexArray>();
	m_VAO->AddVertexBuffer(m_VBO);
	m_VAO->SetIndexBuffer(m_IBO);



	//glGenBuffers(1, &VBO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glGenVertexArrays(1, &VAO);
	//glBindVertexArray(VAO);

	//glGenBuffers(1, &IBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

}


void QuadTessellationScene::ProcessInput(float dt, float dx, float dy)
{
}
void QuadTessellationScene::Update(float dt)
{
	m_gui.CreateFrame();
}


void QuadTessellationScene::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	//Use ImGui to allow user to modify tessellation levels for each edge
	static int outer_left{ 1 };
	static int outer_bottom{ 1 };
	static int outer_right{ 1 };
	static int outer_top{ 1 };

	static int inner_u{ 1 }; //horizontal ->
	static int inner_v{ 1 }; //vertical ^





	//Configure GUI
	ImGui::Begin("Control Points");

	ImGui::Text("Outer");
	ImGui::SliderInt("Left", &outer_left, 1, 8);
	ImGui::SliderInt("Bottom", &outer_bottom, 1, 8);
	ImGui::SliderInt("Right", &outer_right, 1, 8);
	ImGui::SliderInt("Top", &outer_top,1, 8);

	ImGui::Text("Inner");
	ImGui::SliderInt("Horizontal", &inner_u, 1, 8);
	ImGui::SliderInt("Vertical", &inner_v, 1, 8);

	ImGui::End();

	m_shader.Use();
	m_shader.SetInt("Outer[0]", outer_left);
	m_shader.SetInt("Outer[1]", outer_bottom);
	m_shader.SetInt("Outer[2]", outer_right);
	m_shader.SetInt("Outer[3]", outer_top);

	m_shader.SetInt("Inner[0]", inner_u);
	m_shader.SetInt("Inner[1]", inner_v);



	//Bind shader, pass uniforms
	m_VAO->Bind();
	//glBindVertexArray(VAO);
	glDrawElements(GL_PATCHES, m_IBO->Count(), GL_UNSIGNED_INT, 0); //8 indices (4 per patch)
	m_VAO->Unbind();

	m_gui.Render();
}