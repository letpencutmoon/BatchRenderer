/*
filename:VertexArray.h
author:south
update:23.08.24
*/

#pragma once

#include "VertexBuffer.h"

class VertexBufferLayout;

/// @brief 顶点数组类，用于提升数据传输效率
class VertexArray
{
private:
    /// @brief 顶点数组ID
    unsigned int m_RendererID;
public:
    /// @brief 创建并绑定一个顶点数组
    VertexArray();
    /// @brief 删除当前顶点数组
    ~VertexArray();
    /// @brief 绑定当前顶点数组
    void Bind() const;
    /// @brief 解绑当前顶点数组
    void UnBind() const;

    /// @brief 为当前顶点数组添加数据和该数据的内存结构
    /// @param vb 顶点数据缓存
    /// @param Layout 一个顶点的数据格式
    void AddBuffer(const VertexBuffer& vb,const VertexBufferLayout& Layout);
};
