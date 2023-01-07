#include "curve_tessellation.h"
#include <array>
/*
A scene that demonstrates tessellation of curves (Bezier)
Also demonstrates the use of dynamic vertex buffers

*/

/*
TODO: Refactor buffer classes to add support for dynamic buffers

*/

CurveTessellationScene::CurveTessellationScene(GLFWwindow* window)
	:   m_window{ *window }, 
		m_shader{ "examples/Tessellation/Curve/CurveShader.vert", "examples/Tessellation/Curve/CurveShader.frag",
				 "examples/Tessellation/Curve/CurveShader.tesc","examples/Tessellation/Curve/CurveShader.tese" },
		m_cube_shader{"shaders/3DDefaultShader.vert", "shaders/3DDefaultShader.frag" },
		m_gui{window},
		
		//Entities
		m_cube{ 0.05f, 0.05f }

{
	m_camera.Reset(glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, 1.f, 0.f));
	glPatchParameteri(GL_PATCH_VERTICES, 4); //number of vertices per patch

	//Set up dynamic buffer objects for control points
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 12* sizeof(float), nullptr, GL_DYNAMIC_DRAW); //allocate enought space for 4 control points (12 floats)

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}


void CurveTessellationScene::ProcessInput(float dt, float dx, float dy)
{
	m_camera.ProcessKeyboardInput(&m_window, dt);
	m_camera.ProcessMouseInput(&m_window, dx,dy);
}
void CurveTessellationScene::Update(float dt)
{
	m_gui.CreateFrame();
	m_camera.Update();
}


void CurveTessellationScene::Render()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.f); 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glEnable(GL_DEPTH_TEST);

	//Use ImGui to allow user to move control points at runtime
	static std::vector<std::array<float,3>> control_points {
		{ -0.5f,-0.5f, 0.f },
		{ -0.25f, 0.5f, 0.f },
		{ 0.f, -0.5f, 0.f },
		{ 0.25f, 0.5f, 0.f }
	};

	static int segments{30};

	//Configure GUI
	ImGui::Begin("Control Points");

	ImGui::SliderFloat3("a", control_points[0].data(), -10.f, 10.f);
	ImGui::SliderFloat3("b", control_points[1].data(), -10.0f, 10.0f);
	ImGui::SliderFloat3("c", control_points[2].data(), -10.0f, 10.0f);
	ImGui::SliderFloat3("d", control_points[3].data(), -10.f, 10.f);
	ImGui::SliderInt("Segments", &segments, 1, 30);

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();

	//Set buffer data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0,					3 * sizeof(float), control_points[0].data());
	glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(float), 3 * sizeof(float), control_points[1].data());
	glBufferSubData(GL_ARRAY_BUFFER, 6 * sizeof(float), 3 * sizeof(float), control_points[2].data());
	glBufferSubData(GL_ARRAY_BUFFER, 9 * sizeof(float), 3 * sizeof(float), control_points[3].data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//Projection & view don't change per object
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glm::mat4 view = m_camera.getView();
	glm::mat4 model = glm::mat4(1.f);

	m_shader.Use();
	m_shader.SetMat4("model", model);
	m_shader.SetMat4("view", view);
	m_shader.SetMat4("projection", projection);
	
	m_shader.SetInt("NumSegments", segments);
	m_shader.SetInt("NumStrips", 1); //This specifies the number of line strips to be generated


	//Bind shader, pass uniforms
	glBindVertexArray(VAO);
	glDrawArrays(GL_PATCHES, 0, 4);
	glBindVertexArray(0);

	//Also draw some shapes at control points
	m_cube_shader.Use();
	m_cube_shader.SetMat4("view", view);
	m_cube_shader.SetMat4("projection", projection);

	std::vector<glm::vec3> translations{ 
		glm::vec3(control_points[0][0],control_points[0][1],control_points[0][2]),
		glm::vec3(control_points[1][0],control_points[1][1],control_points[1][2]),
		glm::vec3(control_points[2][0],control_points[2][1],control_points[2][2]),
		glm::vec3(control_points[3][0],control_points[3][1],control_points[3][2])
	};

	//Move cubes to control points
	for (int i =0; i<translations.size();++i)
	{
		glm::mat4 cube_model = glm::mat4(1.f);
		cube_model = glm::translate(cube_model, translations[i]);
		cube_model = glm::scale(cube_model, glm::vec3(0.05f, 0.05f, 0.05f));

		m_cube_shader.SetMat4("model", cube_model);
		m_cube.Draw(GLPrimitive::TRIANGLE);
	}

	//GUI
	m_gui.Render();
}