/*
filename:VertexBuffer.cpp
author:south
update:23.08.24
*/

#include "VertexBufferLayout.h"

template<>
void VertexBufferLayout::Push<float>(unsigned int count)
{
    VertexBufferElement vbe = { GL_FLOAT,count,GL_FALSE };
    m_Elements.push_back(vbe);
    m_Stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    VertexBufferElement vbe = { GL_UNSIGNED_INT,count,GL_FALSE };
    m_Elements.push_back(vbe);
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    VertexBufferElement vbe = { GL_UNSIGNED_BYTE,count,GL_TRUE };
    m_Elements.push_back(vbe);
    m_Stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}