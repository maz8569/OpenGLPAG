#version 460 core
layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec4 ourColor;

void main()
{
    FragColor = ourColor; // set alle 4 vector values to 1.0
}