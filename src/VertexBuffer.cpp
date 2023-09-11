/*
filename:VertexBuffer.cpp
author:south
update:23.08.24
*/

#include "VertexBuffer.h"
#include "Renderer.h"
#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int capacity)
    :m_Size(0),m_Capacity(capacity)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER,m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, capacity, data, GL_DYNAMIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER,m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER,0);
}

void VertexBuffer::Expand(unsigned int size)
{
    GLCall(glBindBuffer(GL_COPY_READ_BUFFER,m_RendererID));

    GLuint newID;
    GLCall(glGenBuffers(1,&newID));
    GLCall(glBindBuffer(GL_COPY_WRITE_BUFFER,newID));
    GLCall(glBufferData(GL_COPY_WRITE_BUFFER,size,nullptr,GL_DYNAMIC_DRAW));
    
    GLCall(glCopyBufferSubData(GL_COPY_READ_BUFFER,GL_COPY_WRITE_BUFFER,0,0,m_Size));
    GLCall(glDeleteBuffers(1,&m_RendererID));
    m_RendererID = newID;
    m_Capacity = size;
}

void VertexBuffer::SubData(const VertexBuffer &vb)
{
    Bind();
    GLCall(glCopyBufferSubData(vb.m_RendererID,m_RendererID,0,m_Size,vb.GetSize()));
    m_Size += vb.GetSize();
    Unbind();
}

void VertexBuffer::SubData(const void* data,unsigned int size)
{
    Bind();
    GLCall(glBufferSubData(GL_ARRAY_BUFFER,m_Size,size,data));
    m_Size += size;
    Unbind();
}
