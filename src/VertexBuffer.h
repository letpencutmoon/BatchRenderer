/*
filename:VertexBuffer.h
author:south
update:23.08.24
*/

#pragma once
/// @brief 顶点缓存类，保存顶点数据
class VertexBuffer
{
private:
	/// @brief 缓冲区ID
	unsigned int m_RendererID;
	unsigned int m_Size;

public:
	/// @brief 创建一个缓冲区并设置数据
	/// @param data 数据
	/// @param size 数据的字节数
	VertexBuffer(const void* data,unsigned int size);
	/// @brief 删除该缓冲区
	~VertexBuffer();
	
	/// @brief 绑定该缓冲区
	void Bind() const;
	/// @brief 解绑该缓冲区
	void Unbind() const;
	/// @brief 向缓存区添加数据
	/// @param data 数据
	/// @param size 数据的大小(字节)
	void Add(const void* data,unsigned int size);
};
