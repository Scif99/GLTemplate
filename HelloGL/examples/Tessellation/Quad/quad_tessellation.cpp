#include "quad_tessellation.h"

/*
This scene renders two quads, both of which are tessellated using tessellation shaders
- 

*/

QuadTessellationScene::QuadTessellationScene(GLFWwindow* window)
	: m_window{ *window },
	m_shader{ "examples/Tessellation/Quad/QuadShader.vert", "examples/Tessellation/Quad/QuadShader.frag",
			"examples/Tessellation/Quad/QuadShader.tesc", "examples/Tessellation/Quad/QuadShader.tese" },
	m_gui{ window }

{
	m_camera.Reset(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
	glPatchParameteri(GL_PATCH_VERTICES, 4); //number of vertices per patch
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Wireframe mode


	//1 quad = 1 patch
	float vertices[] = {
	//top left
	-0.9f, 0.5f, 
	-0.5f, 0.5f,
	-0.5f, 0.9f, 
	-0.9f, 0.9f,

	//bottom right
	0.5f, -0.9f,
	0.9f,-0.9f,
	0.9f,-0.5f,
	0.5f,-0.5f
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

}


void QuadTessellationScene::ProcessInput(float dt, float dx, float dy)
{
	m_camera.ProcessKeyboardInput(&m_window, dt);
	m_camera.ProcessMouseInput(&m_window, dx, dy);
}
void QuadTessellationScene::Update(float dt)
{
	m_gui.CreateFrame();
	m_camera.Update();
}


void QuadTessellationScene::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	//Use ImGui to allow user to modify tessellation levels for each edge
	static int outer_left{ 2 };
	static int outer_bottom{ 2 };
	static int outer_right{ 2 };
	static int outer_top{ 2 };

	static int inner_u{ 2 }; //horizontal ->
	static int inner_v{ 2 }; //vertical ^





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
	glBindVertexArray(VAO);
	glDrawArrays(GL_PATCHES, 0, 8);

	m_gui.Render();
}