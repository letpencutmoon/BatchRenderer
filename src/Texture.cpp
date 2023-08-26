/*
filename:Texture.cpp
author:south
update:23.08.24
*/

#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(const std::string& path)
    :m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
    //垂直翻转纹理
    stbi_set_flip_vertically_on_load(1);
    //读取文件，并写入长宽
    m_LocalBuffer = stbi_load(path.c_str(),&m_Width,&m_Height,&m_BPP,4);
    //绑定纹理
    GLCall(glGenTextures(1,&m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D,m_RendererID))
    //设置纹理参数,此处设置纹理过小和过大过滤器为线性插值模式
    GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    
    //设置环绕模式为平铺
    GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP));
    GLCall(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_CLAMP));
    
    //设置纹理数据
    GLCall(glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,m_Width,m_Height,0,GL_RGBA,GL_UNSIGNED_BYTE,m_LocalBuffer));
    GLCall(glBindTexture(GL_TEXTURE_2D,0));
    
    //删除在CPU上的数据
    if(m_LocalBuffer) stbi_image_free(m_LocalBuffer);
}

Texture::~Texture()
{
    GLCall(glDeleteTextures(1,&m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
    //激活纹理
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID))
}

void Texture::UnBind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
