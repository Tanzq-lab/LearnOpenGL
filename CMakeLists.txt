cmake_minimum_required(VERSION 3.21)
project(LearnOpenGL)

set(CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include)             # 指定头文件所在的文件夹路径
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/glm-0.9.8.5)         # 指定glm所在的文件夹路径
link_directories(${PROJECT_SOURCE_DIR}/lib)                    # 指定库文件所在的文件夹路径

add_executable(LearnOpenGL main.cpp src/glad.c Shader.cpp Shader.h)

target_link_libraries(LearnOpenGL -lopengl32 ${PROJECT_SOURCE_DIR}/lib/glfw3.dll ) # 链接一个GLFW库