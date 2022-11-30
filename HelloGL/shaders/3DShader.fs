#version 330 core

//in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
//uniform sampler2D ourTexture;

void main()
{
    float ambient_strength = 0.1f;
    vec3 ambient_component = ambient_strength*lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos); 
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse_component = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular_component = specularStrength * spec * lightColor; 

    vec3 result = objectColor * (ambient_component + diffuse_component + specular_component);

    FragColor = vec4(result,1.0); //* texture(ourTexture, TexCoord);
}