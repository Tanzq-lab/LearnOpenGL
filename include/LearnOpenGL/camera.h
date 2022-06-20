//
// Created by Tanzq on 2022-06-20.
//

#ifndef MAIN_CPP_CAMERA_H
#define MAIN_CPP_CAMERA_H


#include <glad/glad.h>
#include <glm/glm.hpp>

// 定义摄像机移动的几种可能选项。用作抽象，以远离特定于窗口系统的输入方法。
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// 摄像机默认参数
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;


// 一个抽象的相机类，用于处理输入并计算OpenGL中使用的相应欧拉角、向量和矩阵。
class Camera
{
public:
    // 摄像机属性
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    // 欧拉角
    float Yaw;
    float Pitch;

    // 摄像机参数
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // 构造函数 --- 向量
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    // 构造函数 --- 标量
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // 返回使用欧拉角和LookAt矩阵计算的视图矩阵
    glm::mat4 GetViewMatrix() const;

    // 处理从任何类似键盘的输入系统接收到的输入。以相机定义的ENUM的形式接受输入参数(从窗口系统中抽象出来)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // 处理从鼠标输入系统接收的输入。期望在x和y方向上的偏移值。
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // 处理从鼠标滚轮事件接收到的输入。只需要垂直轮轴上的输入
    void ProcessMouseScroll(float yoffset);

private:
    // 从更新后的欧拉角中更新向前向量
    void updateCameraVectors();
};


#endif //MAIN_CPP_CAMERA_H
