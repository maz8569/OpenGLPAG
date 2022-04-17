#version 460 core

layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec3 Normal;
layout (location = 1) in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{    
    vec3 I = normalize(Position - cameraPos);
    vec3 R = reflect(I, normalize(Normal));
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}