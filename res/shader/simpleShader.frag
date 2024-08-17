#version 330 core

out vec4 FragColor;
in vec3 vertexColor;
in vec2 texCoord;

uniform sampler2D u_ourTexture;
uniform sampler2D u_smileTexture;
uniform float u_texAlpha;

vec2 newCoord;
void main()
{
    newCoord = texCoord*2;
    FragColor = mix(texture(u_ourTexture, newCoord), texture(u_smileTexture, vec2(1.0-newCoord.x,newCoord.y)), u_texAlpha);
}