#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
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

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 告诉glfw 每当窗口调整大小的时候调用这个函数。
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    /*
     * 渲染循环
     *
     * */
    // while 循环判断 glfw 是否被要求退出。
    while(!glfwWindowShouldClose(window))
    {
        // 在每一帧上面调用输入检测函数。
        processInput(window);

        // 渲染部分
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // 检查是否有事件触发
        glfwSwapBuffers(window);
        // 使用双缓冲来避免图像闪烁问题，前缓冲保存最终输出图像，渲染指令在后缓冲上进行绘制。
        // 该函数就是交换前后缓冲。
        glfwPollEvents();
    }

    // 释放/删除之前的分配的所有资源
    glfwTerminate();
    return 0;
}

// 当窗口大小发生改变的时候回调该函数。
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // 设置渲染尺寸的大小。
    // 前两个控制窗口左下角的位置， 然后就是窗口的宽度和高度。
    glViewport(0, 0, width, height);
}

// 询问相关按键在当前帧是否被按下，并且做出相关反应。
void processInput(GLFWwindow *window)
{
    // 如果 esc 键按下了，就设置当前窗口允许被关闭。紧接着就会停止渲染循环。
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}