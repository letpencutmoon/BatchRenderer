/*
filename:VertexBufferLayout
author:south
update:23.08.24
*/

#pragma once

#include <vector>
#include <GL/glew.h>

#include "Renderer.h"

/// @brief 缓冲元素结构
struct VertexBufferElement
{
    /// @brief 元素类型
    unsigned int type;
    /// @brief 该元素数据数量
    unsigned int count;
    /// @brief 是否标准化
    unsigned char normalized;

    /// @brief 获取该元素的字节数
    /// @param type 元素
    /// @return 该元素的字节数
    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
        case GL_FLOAT: return 4;
        case GL_UNSIGNED_INT: return 4;
        case GL_UNSIGNED_BYTE:return 1;
        default:
            break;
        }
        ASSETS(false);
        return 0;
    }
};

/// @brief 缓存布局类,对元素缓存布局,表示元素缓存中单个顶点的数据结构
class VertexBufferLayout
{
private:
    /// @brief 一个顶点有多少个字节
    unsigned int m_Stride;
    /// @brief 元素数组
    std::vector<VertexBufferElement> m_Elements;

public:
    VertexBufferLayout()
    :m_Stride(0)
    {};
    /// @brief 向元素数组中添加元素，并计算有多少字节
    /// @tparam T 该元素的数据类型
    /// @param count 该元素的数据数量
    template<typename T>
    void Push(unsigned int count);

    /// @brief 获取元素数组
    inline std::vector<VertexBufferElement> GetVertexElements() const {return m_Elements;};
    /// @brief 获取该顶点缓存单个顶点的字节数
    /// @return 字节数
    inline unsigned int GetStride() const {return m_Stride;}
};
