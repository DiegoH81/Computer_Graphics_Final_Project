#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 PixelPosition;

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform bool useTexture;
uniform vec3 color;
uniform vec3 view_pos;
uniform Material material;
uniform Light light;

uniform sampler2D ourTexture;

void main()
{
    if(useTexture)
    {
        FragColor = texture(ourTexture, TexCoord);
    }
    else
    {
        vec3 norm = normalize(Normal);

        // Ambiente
        vec3 ambient = light.ambient * material.ambient;

        // Difusa
        vec3 light_dir = normalize(light.position - PixelPosition);
        float diff = max(dot(norm, light_dir), 0.0);
        vec3 diffuse = light.diffuse * (diff * material.diffuse);

        // Specular
        vec3 view_dir = normalize(view_pos - PixelPosition);
        vec3 reflect_dir = reflect(-light_dir, norm);

        float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
        vec3 specular = light.specular * (material.specular * spec);

        vec3 result = (ambient + diffuse + specular);// * color;

        FragColor = vec4(result, 1.0f);
    }
}