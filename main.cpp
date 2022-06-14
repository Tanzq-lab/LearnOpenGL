#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void processInput(GLFWwindow *window);

// 参数设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// 将顶点着色器的源码硬编码在文件中。
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

// 将片段着色器的源码硬编码在文件中。
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

// 将片段着色器的源码硬编码在文件中。
const char *SecondFragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 1.f, 0.f, 1.0f);\n"
                                   "}\n\0";

int main() {
    /*
     * 初始化 glfw
     *
     * */
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // 上下文主版本号设置为 3 TODO 为什么呢？
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // 上下文次版本号设置为 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 使用核心模式  TODO 为什么要使用核心模式，和其他的模式有什么区别？

#ifdef __APPLE__ // 用于 Mac OS X 系统
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


    // 创建一个窗口,并设置窗口大小及标题。
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); // 释放/删除之前的分配的所有资源
        return -1;
    }
    // 将该窗口的上下文设置为当前线程的主上下文。
    glfwMakeContextCurrent(window);


    /*
     *   初始化 glad
     *   glfwGetProcAddress会根据我们编译的系统定义正确的函数，
     *   这个函数是 用来加载系统相关的OpenGL函数指针地址的函数。
     * */

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 告诉glfw 每当窗口调整大小的时候调用这个函数。
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 创建并编译着色器
    // ------------------------------------
    // 创建顶点着色器
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // 附加到着色器对象上，并进行编译。
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);


    // 检测是否有编译错误
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    // 片段着色器
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    // 检测编译是否出错
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }


    // 链接着色器
    unsigned int shaderProgram = glCreateProgram(); // 创建程序对象
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // 检查链接是否成功
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }


    // 片段着色器
    unsigned int SecondFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(SecondFragmentShader, 1, &SecondFragmentShaderSource, nullptr);
    glCompileShader(SecondFragmentShader);
    // 检测编译是否出错
    glGetShaderiv(SecondFragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(SecondFragmentShader, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    // 链接着色器
    unsigned int SecondShaderProgram = glCreateProgram(); // 创建程序对象
    glAttachShader(SecondShaderProgram, vertexShader);
    glAttachShader(SecondShaderProgram, SecondFragmentShader);
    glLinkProgram(SecondShaderProgram);

    // 检查链接是否成功
    glGetProgramiv(SecondShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(SecondShaderProgram, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }


    // 已经链接完成了，不需要这写着色器对象了，对这些对象进行释放。
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(SecondFragmentShader);

    // 设置顶点数据(和缓冲区)并配置顶点属性
    // ------------------------------------------------------------------
    float firstVertices[] = {
            -0.9f, -0.5f, 0.0f, // 左
            0.f, -0.5f, 0.0f, // 右
            -0.4f, 0.5f, 0.0f  // 上
    };

    float secondVertices[] = {
            0.f, -0.5f, 0.0f, // 左
            .9f, -0.5f, 0.0f, // 右
            0.4f, 0.5f, 0.0f  // 上
    };

    unsigned int VBOs[2], VAOs[2];
    glGenBuffers(2, VBOs);  // 生成顶点缓冲对象
    glGenVertexArrays(2, VAOs); // 生成顶点数组对象

    // 保存第一个三角形的VAO
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstVertices), firstVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);

    // 保存第二个三角形的VAO
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondVertices), secondVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) nullptr);
    glEnableVertexAttribArray(0);



    // 注意，这是允许的，对glVertexAttribPointer的调用注册了VBO作为顶点属性的绑定顶点缓冲区对象，这样之后我们就可以安全地解除绑定.
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 你可以在之后解除VAO的绑定，这样其他VAO调用就不会意外地修改这个VAO，但这种情况很少发生。
    // 修改其他的vos需要调用glBindVertexArray，所以当没有直接必要的时候，我们通常不会解绑定vos(或VBOs)。
    glBindVertexArray(0);


    /*
     * 渲染循环
     *
     * */
    // while 循环判断 glfw 是否被要求退出。
    while (!glfwWindowShouldClose(window)) {
        // 在每一帧上面调用输入检测函数。
        processInput(window);

        // 渲染部分
        // ----------------------------------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 激活渲染程序对象
        glUseProgram(shaderProgram);
        // 分别进行绑定，并进行绘画。
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(SecondShaderProgram);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //------------------------------------

        // 检查是否有事件触发
        glfwSwapBuffers(window);
        // 使用双缓冲来避免图像闪烁问题，前缓冲保存最终输出图像，渲染指令在后缓冲上进行绘制。
        // 该函数就是交换前后缓冲。
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram);

    // 释放/删除之前的分配的所有资源
    glfwTerminate();
    return 0;
}

// 当窗口大小发生改变的时候回调该函数。
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // 设置渲染尺寸的大小。
    // 前两个控制窗口左下角的位置， 然后就是窗口的宽度和高度。
    glViewport(0, 0, width, height);
}

// 询问相关按键在当前帧是否被按下，并且做出相关反应。
void processInput(GLFWwindow *window) {
    // 如果 esc 键按下了，就设置当前窗口允许被关闭。紧接着就会停止渲染循环。
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}