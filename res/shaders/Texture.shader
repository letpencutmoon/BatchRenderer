#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
//输出该点对应的纹理坐标
out vec2 v_TexCoord;
//变换矩阵
uniform mat4 u_MVP;

void main()
{
    gl_Position =u_MVP * position;
    v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    //根据纹理和纹理坐标获取颜色
    vec4 texColor = texture(u_Texture,v_TexCoord);
    color = texColor;
};

