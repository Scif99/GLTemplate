#version 330 core

//in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light; 

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
//uniform sampler2D ourTexture;

void main()
{
    vec3 ambient_component = material.ambient*light.ambient;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos); 
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse_component = material.diffuse*diff * light.diffuse;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm); 
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular_component = material.specular * spec * light.specular; 

    vec3 result = ambient_component + diffuse_component + specular_component;

    FragColor = vec4(result,1.0); //* texture(ourTexture, TexCoord);
}