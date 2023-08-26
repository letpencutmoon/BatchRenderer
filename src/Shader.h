/*
filename:Shader.h
author:south
update:23.08.24
*/
#pragma once

#include<string>
#include<unordered_map>
#include "glm/glm.hpp"

/// @brief 
struct ShaderProgramSource
{
    std::string VetexShader;
    std:: string FragmentShader;
};

/// @brief 着色器类，控制着色器的编译使用
class Shader
{
public:
    /// @brief 读取着色器文件并传入GPU编译
    /// @param filepath 
    Shader(const std::string& filepath);
    /// @brief 删除编译好的程序
    ~Shader();
    /// @brief 使用当前程序
    void Bind() const;
    /// @brief 解绑当前程序
    void UnBind() const;

    /// @brief 设置统一变量
    /// @param name 统一变量名称
    /// @param value 统一变量值
    void SetUniform1i(const std::string& name,int value);
    void SetUniform1f(const std::string& name, int value);
    void SetUniform4f(const std::string& name,float v0,float v1,float f0,float f1);
    void SetUniformMat4f(const std::string& name,const glm::mat4& matrix);

    /// @brief 根据源码创建着色器程序并返回该程序id
    /// @param vertexShader 顶点着色器源码
    /// @param fragmentShader 像素着色器源码
    /// @return 着色器程序ID
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

private:
    /// @brief 着色器程序ID
    unsigned int m_RendererID;
    /// @brief 着色器文件路径
    std::string m_FilePath;
    /// @brief 统一变量缓存
    std::unordered_map<std::string,int> m_UniformLocationCahe;
private:
    /// @brief 获取统一变量的ID
    /// @param name 统一变量名称
    /// @return 统一变量ID
    int GetUniformLocation(const std::string& name);

    /// @brief 编译着色器源码
    /// @param source 着色器源码
    /// @param type 着色器类型
    /// @return 着色器ID
    unsigned int CompileShader(const std::string& source, unsigned int type);

    /// @brief 读取文件，获取着色器源码
    /// @return 着色器源码
    ShaderProgramSource ParseShader();
};
