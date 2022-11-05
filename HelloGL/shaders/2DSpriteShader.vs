#version 330 core
layout (location = 0) in vec2 a_pos;
layout (location = 1) in vec2 a_tex_coord; 


uniform mat4 model;
uniform mat4 projection;

out vec2 TexCoord;

void main()
{
    TexCoord = a_tex_coord;
    gl_Position =  projection * model * vec4(a_pos.xy, 0.0, 1.0);

}