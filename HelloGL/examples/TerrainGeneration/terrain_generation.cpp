#include "terrain_generation.h"

inline const unsigned int SCREEN_WIDTH = 800;
inline const unsigned int SCREEN_HEIGHT = 600;


TerrainGenerationScene::TerrainGenerationScene(GLFWwindow* window)
    :
    m_window{ *window },
    m_gui{ window },
    //Shaders
    m_shader{ GLShader("examples/TerrainGeneration/TessHeightmapShader.vert", "examples/TerrainGeneration/TessHeightmapShader.frag",
    "examples/TerrainGeneration/TessHeightmapShader.tesc", "examples/TerrainGeneration/TessHeightmapShader.tese") },
    //Textures
    m_heightmap{ "examples/TerrainGeneration/HeightMaps/iceland_heightmap.png" },
    //Entities
    m_terrain{ m_heightmap} 
{
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Wireframe mode
    glPatchParameteri(GL_PATCH_VERTICES, 4);

    //Move camera to a slightly better position
    m_camera.Reset(glm::vec3(67.0f, 27.5f, 169.9f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));
}

void TerrainGenerationScene::ProcessInput(float dt, float dx, float dy)
{
    m_camera.ProcessKeyboardInput(&m_window, dt);
    m_camera.ProcessMouseInput(&m_window, dx, dy);
}

void TerrainGenerationScene::Update(float dt)
{
    m_gui.CreateFrame();
    m_camera.Update();
}


void TerrainGenerationScene::Render()
{

    ImGui::Begin("Scene Menu");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    glClearColor(0.1f, 0.1f, 0.1f, 1.f); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glEnable(GL_DEPTH_TEST);

    //Projection & view don't change per object
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100000.0f);
    glm::mat4 view = m_camera.getView();
    glm::mat4 model = glm::mat4(1.f);   

    //Bind shader, pass uniforms
    m_shader.Use();
    m_heightmap.Bind();
    m_shader.SetInt("heightMap", 0);
    m_shader.SetMat4("projection", projection);
    m_shader.SetMat4("view", view);
    m_shader.SetMat4("model", model);

    m_terrain.m_VAO->Bind();
    glDrawElements(GL_PATCHES, m_terrain.m_IBO->Count(), GL_UNSIGNED_INT, 0);
    m_terrain.m_VAO->Unbind();


    m_gui.Render();
}