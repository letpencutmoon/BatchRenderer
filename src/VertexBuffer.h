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

	void Expand(unsigned int size);

	void SubData(const VertexBuffer& vb);
	void SubData(const void* data,unsigned int size);

	inline unsigned int GetSize() const {return m_Size;};
};
