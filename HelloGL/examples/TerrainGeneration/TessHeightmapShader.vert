#version 430 core

layout(location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 TexCoord;

void main()
{
	//Notice how we don't apply the MVP here, instead we apply it in the .tese shader
	gl_Position = vec4(aPos, 1.0);
	TexCoord = aTex;
}