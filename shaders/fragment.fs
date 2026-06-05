#version 330 core
out vec4 FragColor;
in vec2 TexCoord;

uniform bool useTexture;
uniform vec3 color;
uniform sampler2D ourTexture;

void main()
{
    if(useTexture)
    {
        FragColor = texture(ourTexture, TexCoord);
    }
    else
    {
        FragColor = vec4(color, 1.0f);
    }
}