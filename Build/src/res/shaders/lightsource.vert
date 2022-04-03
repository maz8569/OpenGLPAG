#version 460 core
layout (location = 0) in vec3 aPos;

layout (location = 0) out vec4 ourColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec4 aColor;

void main()
{
    ourColor = aColor;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}