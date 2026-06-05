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

uniform bool useTexture;
uniform vec3 color;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;
uniform Material material;

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
        vec3 ambient = material.ambient * light_color;

        // Difusa
        vec3 light_dir = normalize(light_pos - PixelPosition);
        float diff = max(dot(norm, light_dir), 0.0);
        vec3 diffuse = light_color * (diff * material.diffuse);

        // Specular
        vec3 view_dir = normalize(view_pos - PixelPosition);
        vec3 reflect_dir = reflect(-light_dir, norm);

        float spec = pow(max(dot(view_dir, reflect_dir), 0.0), material.shininess);
        vec3 specular = light_color * (material.specular * spec);

        vec3 result = (ambient + diffuse + specular) * color;

        FragColor = vec4(result, 1.0f);
    }
}