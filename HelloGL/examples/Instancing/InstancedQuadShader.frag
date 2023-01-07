#version 330 core
out vec4 FragColor;

uniform sampler2D Texture;
in vec2 TexCoord;

void main()
{

    FragColor = vec4(texture(Texture, TexCoord.xy,1.f));
}