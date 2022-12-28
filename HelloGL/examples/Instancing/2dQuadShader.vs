#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aOffset; //Per-instance rather than per-vertex

out vec3 fColor;

uniform float t;

void main()
{
    //gl_Position = vec4(aPos, 0.0, 1.0);

    gl_Position = vec4(aPos.x + aOffset.x + sin(t), aPos.y + aOffset.y, 0.0, 1.0);
    fColor = aColor;
}  