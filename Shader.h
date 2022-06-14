//
// Created by Tanzq on 2022-06-14.
//

#ifndef MAIN_CPP_SHADER_H
#define MAIN_CPP_SHADER_H


#include "glad/glad.h"

#include <string>

class Shader
{
public:
    unsigned int ID;
    // 构造函数动态生成着色器
    // ------------------------------------------------------------------------
    Shader(const char* vertexPath, const char* fragmentPath);

    // 激活渲染器
    // ------------------------------------------------------------------------
    void use() const;

    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const;
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const;
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const;


private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(unsigned int shader, const std::string& type);

};

#endif //MAIN_CPP_SHADER_H
