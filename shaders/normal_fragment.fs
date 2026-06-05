#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 PixelPosition;

uniform bool useTexture;
uniform vec3 color;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

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
        float ambient_strenght = 0.3f;
        vec3 ambient = ambient_strenght * light_color;

        // Difusa
        vec3 light_dir = normalize(light_pos - PixelPosition);
        float diff = max(dot(norm, light_dir), 0.0);
        vec3 diffuse = diff * light_color;

        // Specular
        float specular_strength = 0.5;
        vec3 view_dir = normalize(view_pos - PixelPosition);
        vec3 reflect_dir = reflect(-light_dir, norm);

        float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 32);
        vec3 specular = specular_strength * spec * light_color;  

        vec3 result = (ambient + diffuse + specular) * color;

        FragColor = vec4(result, 1.0f);
    }
}