#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

// 纹理采样器
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float alpha;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2,   vec2(TexCoord.x, TexCoord.y)), alpha);
}