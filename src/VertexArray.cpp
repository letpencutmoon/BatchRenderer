/*
filename:VertexArray.cpp
author:south
update:23.08.24
*/

#include "VertexArray.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1,&m_RendererID));
    GLCall(glBindVertexArray(m_RendererID));
}

VertexArray::VertexArray(VertexBufferLayout& layout)
    :m_Count(0),m_Capacity(10)
{
    m_Layout = std::make_unique<VertexBufferLayout>(layout);
    GLCall(glGenVertexArrays(1,&m_RendererID));
    GLCall(glBindVertexArray(m_RendererID));
    m_Buffer = std::make_unique<VertexBuffer>(nullptr,layout.GetStride() * 10);
    SetLayout();
}

VertexArray::~VertexArray()
{
    GLCall(glDeleteVertexArrays(1,&m_RendererID));
}

void VertexArray::Bind() const
{
    GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::UnBind() const
{
    GLCall(glBindVertexArray(0));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    vb.Bind();
    Bind();
    const auto& elements = layout.GetVertexElements();
    unsigned int offset = 0;
    for (unsigned int i = 0;i < elements.size();i++)
    {
        const auto element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i,element.count,element.type,
            element.normalized,layout.GetStride(),(const void*)(uintptr_t)offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::AddBuffer(const VertexBuffer& vb)
{
    int newCount = vb.GetSize() / m_Layout->GetStride() + m_Count;
    EnsureCapacity(newCount);
    m_Buffer->SubData(vb);
    m_Count = newCount;
}

void VertexArray::AddBuffer(const void* data,unsigned int size)
{
    m_Count = size / m_Layout->GetStride() + m_Count;
    EnsureCapacity(m_Count);
    m_Buffer->SubData(data,size);
}

void VertexArray::SetLayout()
{
    m_Buffer->Bind();
    Bind();
    const auto& elements = m_Layout->GetVertexElements();
    unsigned int offset = 0;
    for (unsigned int i = 0;i < elements.size();i++)
    {
        const auto element = elements[i];
        GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i,element.count,element.type,
            element.normalized,m_Layout->GetStride(),(const void*)(uintptr_t)offset));
        offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::EnsureCapacity(int minCapacity)
{
    if(m_Capacity <= minCapacity)
    {
        m_Count = minCapacity;
        m_Capacity = minCapacity + 10;
        m_Buffer->Expand(m_Capacity * m_Layout->GetStride());
        SetLayout();
    }
}
