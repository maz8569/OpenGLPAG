#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in mat4 instanceMatrix;

layout (location = 0) out vec4 ourColor;
layout (location = 1) out vec2 TexCoord;
layout (location = 2) out vec3 Normal;
layout (location = 3) out vec3 FragPos;

uniform mat4 view;
uniform mat4 projection;
uniform vec4 aColor;

void main()
{
    ourColor = aColor;
    TexCoord = aTexCoord;
    FragPos = vec3(instanceMatrix * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(instanceMatrix))) * aNormal;

    gl_Position = projection * view * instanceMatrix * vec4(aPos, 1.0f);
}