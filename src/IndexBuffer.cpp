/*
filename:IndexBuffer.cpp
author:south
update:23.08.24
*/

#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data,unsigned int count)
	:m_Count(count)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()	
{
	GLCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

void IndexBuffer::Add(const unsigned int *data, unsigned int count)
{
	GLuint newID;
	GLCall(glGenBuffers(1,&newID));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,newID));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER,(m_Count + count) * sizeof(unsigned int),nullptr,GL_STATIC_DRAW));
	GLCall(glCopyBufferSubData(m_RendererID,newID,0,0,m_Count * sizeof(unsigned int)));
	GLCall(glBufferSubData(newID,m_Count * sizeof(unsigned int),count * sizeof(unsigned int),data));

	glDeleteBuffers(1,&m_RendererID);
	m_RendererID = newID;
}
