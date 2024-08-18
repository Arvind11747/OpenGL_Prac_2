#version 330 core

out vec4 FragColor;
in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D u_ourTexture;
uniform sampler2D u_smileTexture;
uniform float u_texAlpha;

void main()
{
    FragColor = mix(texture(u_ourTexture, texCoord), texture(u_smileTexture, texCoord), u_texAlpha);
}