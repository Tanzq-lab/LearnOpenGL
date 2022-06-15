#version 330 core
out vec4 FragColor;

in vec3 ourLocation;

void main()
{
    FragColor = vec4(ourLocation, 1.0f);
}