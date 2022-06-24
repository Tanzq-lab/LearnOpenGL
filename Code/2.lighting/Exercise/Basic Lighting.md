# 基础光照作业

- 目前，我们的光源是静止的，你可以尝试使用sin或cos函数让光源在场景中来回移动。观察光照随时间的改变能让你更容易理解冯氏光照模型。



可以在渲染循环中添加下面这行代码：

`lightPos.z = static_cast<float>(sin(glfwGetTime()));`



- 尝试使用不同的环境光、漫反射和镜面强度，观察它们怎么是影响光照效果的。同样，尝试实验一下镜面光照的反光度因子。尝试理解为什么某一个值能够有着某一种视觉输出。



![LightTest](Images/LightTest.gif)



- 在观察空间（而不是世界空间）中计算冯氏光照。

顶点着色器：

```glsl
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;
out vec3 LightPos; // 观察空间下的

// 在顶点着色器中定义uniform ，作用是通过这个坐标转化成观察空间下的光源位置输出给片段着色器。
uniform vec3 lightPos; // 世界坐标系下的。

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * vec4(FragPos, 1.0);
    LightPos = vec3(view * vec4(lightPos, 1.0)); // 将光源坐标从世界坐标变换成观察坐标。
}
```

片段着色器：

```glsl
#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

//uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform float ambientStrength;
uniform float specularStrength;
uniform int Shininess;
uniform bool closeDiffuse;

void main()
{
    // 环境光照
//    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    // 漫射光照
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    if (closeDiffuse) diffuse = vec3(0.f);


    // 镜面光照
//    float specularStrength = 1.f;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), Shininess);
    vec3 specular = specularStrength * spec * lightColor;


    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
```





- 尝试实现一个Gouraud着色（而不是冯氏着色）。如果你做对了话，立方体的光照应该会看起来有些奇怪，尝试推理为什么它会看起来这么奇怪。



就是将片段着色器计算的东西放到顶点着色器进行计算。有着不同的效果。

主要是顶点着色器插值精度不太高。