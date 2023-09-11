/*
filename:VertexBuffer.cpp
author:south
update:23.08.24
*/

#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
    :m_Size(size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER,m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
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
    GLuint newID;
    GLCall(glGenBuffers(1,&newID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER,newID));
    GLCall(glBufferData(GL_ARRAY_BUFFER,size,nullptr,GL_DYNAMIC_DRAW));
    GLCall(glCopyBufferSubData(m_RendererID,newID,0,0,size));
    GLCall(glDeleteBuffers(1,&m_RendererID));
    m_RendererID = newID;
    m_Size = size;
}

void VertexBuffer::SubData(const VertexBuffer &vb)
{
    Bind();
    GLCall(glCopyBufferSubData(vb.m_RendererID,m_RendererID,0,m_Size,vb.GetSize()));
    Unbind();
}

void VertexBuffer::SubData(const void *data,unsigned int size)
{
    Bind();
    GLCall(glBufferSubData(m_RendererID,m_Size,size,data));
    Unbind();
}
