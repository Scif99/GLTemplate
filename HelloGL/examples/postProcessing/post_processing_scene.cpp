    #include "post_processing_scene.h"

inline const unsigned int SCREEN_WIDTH = 800;
inline const unsigned int SCREEN_HEIGHT = 600;


PostProcessingScene::PostProcessingScene(GLFWwindow* window)
    :
    m_window{ *window },
    //Shaders
    m_material_shader{ GLShader("shaders/3DMaterialShader.vert", "shaders/3DMaterialShader.frag") },
    m_light_source_shader{ "shaders/3DDefaultShader.vert", "shaders/3DDefaultShader.frag" },
    m_frame_buffer_shader{ "examples/postProcessing/SharpenShader.vert", "examples/postProcessing/SharpenShader.frag" },
    //Textures
    m_container_diffuse_map{ "assets/textures/container2.png", "diffuse" },
    m_container_specular_map{ "assets/textures/container2_specular.png", "specular" },
    m_tiles_texture{ "assets/textures/tiles.jpg", "floor" },
    //Framebuffer
    m_framebuffer{ SCREEN_WIDTH, SCREEN_HEIGHT },
    //Entities
    m_light{ LightCube::s_default_pos, LightCube::s_default_ambient, LightCube::s_default_diffuse, LightCube::s_default_specular },
    m_terrain{ 2.f,2.f, 2 },
    m_frame_quad{1.f, 1.f},
    m_container{1.f, 1.f}
{
}

void PostProcessingScene::ProcessInput(float dt, float dx, float dy)
{
    m_camera.ProcessKeyboardInput(&m_window, dt);
    m_camera.ProcessMouseInput(&m_window, dx, dy);
}

void PostProcessingScene::Update(float dt)
{
    m_camera.Update();
}


void PostProcessingScene::Render()
{
    ////first pass using our custom framebuffer
    m_framebuffer.Bind();
    glClearColor(0.1f, 0.1f, 0.1f, 1.f); //state-setting
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //state-using
    glEnable(GL_DEPTH_TEST);

    //Projection & view don't change per object
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = m_camera.GetView();

    //-------------------
    // WOODEN CONTAINER
    //---------------
    //Bind shader, pass uniforms
    m_material_shader.Use();
    m_material_shader.SetMat4("projection", projection);
    m_material_shader.SetMat4("view", view);
    m_material_shader.SetVec3("viewPos", m_camera.Position());

    m_material_shader.SetFloat("material.shininess", 64.f);

    //**TODO add a SetMaterial(amb, diff, spec) function?**
    m_material_shader.SetVec3("light.position", m_light.m_position);
    m_material_shader.SetVec3("light.ambient", m_light.m_ambient);
    m_material_shader.SetVec3("light.diffuse", m_light.m_diffuse); // darken diffuse light a bit
    m_material_shader.SetVec3("light.specular", m_light.m_specular);


    //Model
    glm::mat4 container_model = glm::mat4(1.f);
    container_model = glm::translate(container_model, glm::vec3(0.f, 0.52f, 0.f));
    m_material_shader.SetMat4("model", container_model);

    //draw
    m_container_diffuse_map.Bind(0);
    m_container_specular_map.Bind(1);
    m_container.Draw(GLPrimitive::TRIANGLE);


    //------------------------
    //TERRAIN
    //-----------------------
    //using same shader as container... so all uniforms are set already.... just need to compute model

    //Model
    glm::mat4 floor_model = glm::mat4(1.f);
    floor_model = glm::scale(floor_model, glm::vec3(5.f));
    m_material_shader.SetMat4("model", floor_model);

    //Draw
    m_tiles_texture.Bind(0);
    m_tiles_texture.Bind(1);
    m_terrain.Draw(GLPrimitive::TRIANGLE);


    //-----------
    //LIGHT SOURCE
    //-------------

    //Configure shader, pass uniforms
    m_light_source_shader.Use();
    m_light_source_shader.SetMat4("projection", projection);
    m_light_source_shader.SetMat4("view", view);

    //Model
    glm::mat4 Lightmodel = glm::mat4(1.f);
    Lightmodel = glm::translate(Lightmodel, m_light.m_position);
    Lightmodel = glm::scale(Lightmodel, glm::vec3(0.2f));
    m_light_source_shader.SetMat4("model", Lightmodel);

    //Draw
    m_container.Draw(GLPrimitive::TRIANGLE);

    // SECOND PASS (Framebuffer)
    m_framebuffer.Unbind();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_DEPTH_TEST);

    m_frame_buffer_shader.Use();
    m_framebuffer.m_texture_object.Bind();
    m_frame_quad.Draw(GLPrimitive::TRIANGLE);
}