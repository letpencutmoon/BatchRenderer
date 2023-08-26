/*
filename:Texture.h
author:south
update:23.08.24
*/

#include "Renderer.h"

/// @brief 纹理类，设置一个纹理在GPU上
class Texture
{
private:
    /// @brief 纹理ID
    unsigned int m_RendererID;
    /// @brief 纹理文件的路径
    std::string m_FilePath;
    /// @brief 纹理文件读取的数据
    unsigned char* m_LocalBuffer;
    /// @brief 长，宽，每个像素的位数
    int m_Width,m_Height,m_BPP;
public:
    /// @brief 根据路径设置一个纹理并保存这个纹理的各项数据
    /// @param path 纹理文件的路径
    Texture(const std::string& path);
    /// @brief 删除GPU中的该纹理
    ~Texture();

    /// @brief 绑定纹理到slot纹理槽
    /// @param slot 纹理槽，最多32个
    void Bind(unsigned int slot = 0) const;
    /// @brief 解绑纹理
    void UnBind() const;

    /// @brief 获取纹理的宽
    inline int GetWidth() {return m_Width;}
    /// @brief 获取纹理的高
    inline int GetHeight() {return m_Height;}
};