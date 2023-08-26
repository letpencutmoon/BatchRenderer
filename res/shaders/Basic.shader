/*
filename:Basic.shader
author:south
*/

//顶点着色器，用于确定顶点位置
#shader vertex
#version 330 core
layout(location = 0) in vec4 position;

void main()
{
	gl_Position = position;
};

//颜色着色器，确定顶点颜色
#shader fragment
#version 330 core
layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main()
{
	color = u_Color;
};

 