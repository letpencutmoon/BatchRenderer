/*
filename:IndexBuffer.h
author:south
update:23.8.24
*/

#pragma once

/// @brief 顶点缓冲区类，存储放在顶点缓冲区的数据
class IndexBuffer
{
private:
	/// @brief 缓冲区ID
	unsigned int m_RendererID;
	/// @brief 缓冲区数据数量
	unsigned int m_Count;

public:
	/// @brief 生成单个缓冲区，绑定缓冲区设置数据
	/// @param data 
	/// @param count
	IndexBuffer(const unsigned int* data,unsigned int count);
	/// @brief 删除缓冲区
	~IndexBuffer();

	/// @brief 绑定和解绑该缓冲区
	void Bind() const;
	void Unbind() const;
	/// @brief 获取数据数量
	/// @return m_Count
	inline unsigned int GetCount() const{ return m_Count;}

	/// @brief 向内存中添加顶点下标数据 
	/// @param data 顶点下标数据
	/// @param count 数据数量
	void Add(const unsigned int* data,unsigned int count);
};