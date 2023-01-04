#include "terrain_generation.h"

inline const unsigned int SCREEN_WIDTH = 800;
inline const unsigned int SCREEN_HEIGHT = 600;

constexpr int MESH_VERTICES_X{ 64 };
constexpr int MESH_VERTICES_Z{ 64 };

TerrainGenerationScene::TerrainGenerationScene(GLFWwindow* window)
    : 
    m_window{ *window },
    //Shaders
    //m_shader{ GLShader("examples/TerrainGeneration/WaveShader.vs", "examples/TerrainGeneration/WaveShader.fs") },
    m_shader{ GLShader("examples/TerrainGeneration/HeightmapShader.vs", "examples/TerrainGeneration/HeightmapShader.fs") },
    //m_water_texture{ "assets/textures/water.jpg", false, "water" },
    m_gui{window},

    //Entities
    m_terrain{ "examples/TerrainGeneration/HeightMaps/iceland_heightmap.png"} 
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Wireframe mode
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
    //std::cout << m_camera.Position().x << ',' << m_camera.Position().y << ',' << m_camera.Position().z << '\n';
}


void TerrainGenerationScene::Render()
{
    //**WHAT IF WE WANT MULTIPLE IMGUI WINDOWS?**

    static int t{ 32 };
    static float k{ 5.f };
    static float v{ 1.f };
    static float a{ 1.f };

    ImGui::Begin("Scene Menu");
    ImGui::SliderFloat("K", &k, 1.f, 10.f);           
    ImGui::SliderFloat("Velocity", &v, 0.0f, 5.0f);      
    ImGui::SliderFloat("Amp", &a, 0.0f, 5.0f);           
    ImGui::SliderInt("Tesselation", &t, 2, 128);           

    
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();


    glClearColor(0.1f, 0.1f, 0.1f, 1.f); //state-setting
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //state-using
    glEnable(GL_DEPTH_TEST);

    //Projection & view don't change per object
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100000.0f);
    glm::mat4 view = m_camera.getView();


    //Bind shader, pass uniforms
    m_shader.Use();
    m_shader.SetMat4("projection", projection);
    m_shader.SetMat4("view", view);


    //m_shader.SetFloat("Time", (float)glfwGetTime());
    //m_shader.SetFloat("K", k);
    //m_shader.SetFloat("Velocity", v);
    //m_shader.SetFloat("Amp", a);
    //m_terrain = TerrainMesh(t, t);
    glm::mat4 model = glm::mat4(1.f);
    //model = glm::scale(model, glm::vec3(2624.f / 2.f, 1.f, 1756.f / 2.f)); //Scale based on the resolution of the heightmap
    m_shader.SetMat4("model", model);

    //m_water_texture.Bind(0);
    m_terrain.Draw();

    m_gui.Render();
}