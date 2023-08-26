/*
filename:Renderer.h
author:south
update:23.08.24
*/

#pragma once
#include<GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

//如果x是false就直接停止程序
#define ASSETS(x) if(!(x)) __builtin_trap();
//判断当前执行的函数是否有错误
#define GLCall(x) GLClearError();\
    x;\
    ASSETS(GLLogCall(#x,__FILE__,__LINE__))

/// @brief 清除已有gl错误
void GLClearError();

/// @brief 打印gl错误的具体位置并返回是否有错误
bool GLLogCall(const char* function, const char* file, int line);

class Renderer
{
public:
    /// @brief 根据数据绘制图形
    /// @param va 顶点数组
    /// @param ib 顶点缓冲区
    /// @param shader 着色器
    void Draw(const VertexArray& va,const IndexBuffer& ib,const Shader& shader) const;
    /// @brief 以默认颜色清除屏幕
    void Clear() const;
    /// @brief 设定默认颜色
    void SetClearColor();
private:
};

