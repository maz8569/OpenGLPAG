#version 460 core

layout (location = 0) out vec4 FragColor;

layout (location = 0) in vec3 Normal;
layout (location = 1) in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{    
    vec3 ratio = 1.00 / vec3(1.52) + vec3(0.0, 0.1, 0.2);
    //float ratio = 1.0 / 1.52;
    vec3 I = normalize(Position - cameraPos);
    vec3 refract_dir_r = refract(I, normalize(Normal), ratio.r);
    vec3 refract_dir_g = refract(I, normalize(Normal), ratio.g);
    vec3 refract_dir_b = refract(I, normalize(Normal), ratio.b);
    //vec3 refract_dir = refract(I, normalize(Normal), ratio);
    vec3 reflect_dir = reflect(I, normalize(Normal));

    //vec4 refract_color = texture(skybox, refract_dir);
    
    float refract_color_r = texture(skybox, refract_dir_r).r;
    float refract_color_g = texture(skybox, refract_dir_g).g;
    float refract_color_b = texture(skybox, refract_dir_b).b;

    vec4 refract_color = vec4(refract_color_r, refract_color_g, refract_color_b, 1.0);
    vec4 reflect_color = texture(skybox, reflect_dir);

    //float alpha = max(0.0, dot(I, normalize(Normal)));
    FragColor = mix(refract_color, reflect_color, 0.2);
    //FragColor = vec4(texture(skybox, refract_dir).rgb, 1.0);
    //FragColor = vec4(0, 0, 0,0);
}