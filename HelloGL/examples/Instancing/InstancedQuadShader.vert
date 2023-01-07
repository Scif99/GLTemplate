#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec2 aOffset; //Per-instance rather than per-vertex

out vec3 fColor;
out vec2 TexCoord;

uniform float t;

void main()
{

    gl_Position = vec4(aPos.x + aOffset.x + sin(t), aPos.y + aOffset.y, aPos.z, 1.0);
    TexCoord = aTexCoord;
}  