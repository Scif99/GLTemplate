#include "application.h"


Application::Application(unsigned int width, unsigned int height)
	:m_keys(), m_width{ width }, m_height{ height }
{

}

void Application::init(GLFWwindow* window)
{
    //Window/GUI stuff
    m_window = window;
    //m_gui = std::make_unique<GUI>(m_window.get());

    // Initialize ImGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    //ImGui::GetIO().ConfigFlags |= ImguiConfigFlafe_//ImGuiConfigFlags_ViewportsEnable; //enabkeviewports
    ImGui_ImplOpenGL3_Init("#version 400 core");

    //Load Shaders
    m_container_shader = std::make_unique<GLShader>("shaders/3dMaterialShader.vs", "shaders/3dMaterialShader.fs");
    m_lightsourceshader = std::make_unique<GLShader>("shaders/LightSourceShader.vs", "shaders/LightSourceShader.fs");

    //Load Textures
    m_diffuse_map = std::make_unique<GLTexture>("assets/textures/container2.png", false, "diffuse");
    m_specular_map = std::make_unique<GLTexture>("assets/textures/container2_specular.png", false, "specular");
    m_tiles = std::make_unique<GLTexture>("assets/textures/tiles.jpg", false, "floor");


    //configure camera
    glm::vec3 cameraPos = glm::vec3(0.0f, 1.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    m_camera = std::make_unique<Camera>(cameraPos, cameraFront, cameraUp);

    //Create Game objects
    
    //set properties of light (doesn't change per frame for now...)
    glm::vec3 light_pos = glm::vec3(1.2f, 1.0f, 2.0f);
    glm::vec3 light_ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 light_diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 light_specular = glm::vec3(1.0f, 1.0f, 1.0f);
    m_light = std::make_unique<LightCube>(light_pos, light_ambient, light_diffuse, light_specular);

    //Wooden Container
    m_container = std::make_unique<Container>();
    m_terrain = std::make_unique<Terrain>();


}


void Application::ProcessInput(float dt, float dx, float dy)
{
    m_camera->ProcessKeyboardInput(m_window, dt);
    m_camera->ProcessMouseInput(m_window, dx, dy);

}

void Application::Update(float dt)
{
    m_camera->Update();

    //m_gui->CreateFrame();

}



void Application::Render()
{
    //GUI
    // //-------------------------------
        // Our state
    bool show_demo_window = true;
    static ImVec4 Light_Specular = ImVec4(0.2f, 0.2f, 0.2f, 1.f);
    static ImVec4 Light_Diffuse = ImVec4(0.5f, 0.5f, 0.5f, 1.f);
    static ImVec4 Light_Ambient = ImVec4(0.2f, 0.2f, 0.2f, 1.f);

    bool show_gui{ false };
    if(show_gui)
    {
        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("Ambient", (float*)&Light_Ambient); // Edit 3 floats representing a color
            ImGui::ColorEdit3("Diffuse", (float*)&Light_Diffuse); // Edit 3 floats representing a color
            ImGui::ColorEdit3("Specular", (float*)&Light_Specular); // Edit 3 floats representing a color



            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
    m_gui->Render();
    }

    //------------------------------------------

    glClearColor(0.f, 0.f, 0.f, 0.f); //state-setting
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //state-using

    //Projection & view don't change per object
    glm::mat4 projection =  glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = m_camera->getView();

    //-------------------
    // WOODEN CONTAINER
    //---------------
    //Bind shader, pass uniforms
    m_container_shader->Use();
    m_container_shader->SetMat4("projection", projection);
    m_container_shader->SetMat4("view", view);
    m_container_shader->SetVec3("viewPos", m_camera->Position());

    m_container_shader->SetFloat("material.shininess", 64.f);

    //**TODO add a SetMaterial(amb, diff, spec) function?**
    m_container_shader->SetVec3("light.position", m_light->m_position);
    //m_container_shader->SetVec3("light.ambient", m_light->m_ambient);
    //m_container_shader->SetVec3("light.diffuse", m_light->m_diffuse); // darken diffuse light a bit
    //m_container_shader->SetVec3("light.specular", m_light->m_specular);

    m_container_shader->SetVec3("light.ambient", glm::vec3(Light_Ambient.x,Light_Ambient.y,Light_Ambient.z));
    m_container_shader->SetVec3("light.diffuse", glm::vec3(Light_Diffuse.x, Light_Diffuse.y, Light_Diffuse.z)); // darken diffuse light a bit
    m_container_shader->SetVec3("light.specular", glm::vec3(Light_Specular.x, Light_Specular.y, Light_Specular.z));

    //Model
    glm::mat4 container_model = glm::mat4(1.f);
    container_model = glm::translate(container_model, glm::vec3(0.f, 0.52f, 0.f));
    m_container_shader->SetMat4("model", container_model);

    //draw
    m_diffuse_map->Bind(0);
    m_specular_map->Bind(1);

    m_container->m_mesh->Draw();


    //------------------------
    //TERRAIN
    //-----------------
    //using same shader as container... so all uniforms are set already.... just need to compute model
    
    //Model
    glm::mat4 floor_model = glm::mat4(1.f);
    floor_model = glm::scale(floor_model, glm::vec3(5.f));
    m_container_shader->SetMat4("model", floor_model);

    //draw
    m_tiles->Bind(0);
    m_tiles->Bind(1);

    m_terrain->m_mesh->Draw();


    //-----------
    //LIGHT SOURCE
    //-------------

    //Configure shader, pass uniforms
    m_lightsourceshader->Use();
    m_lightsourceshader->SetMat4("projection", projection);
    m_lightsourceshader->SetMat4("view", view);

    //Model
    glm::mat4 Lightmodel = glm::mat4(1.f);
    Lightmodel = glm::translate(Lightmodel, m_light->m_position);
    Lightmodel = glm::scale(Lightmodel, glm::vec3(0.2f));
    m_lightsourceshader->SetMat4("model", Lightmodel);

    //Draw
    m_container->m_mesh->Draw();




}

void Application::Cleanup()
{
    m_gui->Cleanup();
}
