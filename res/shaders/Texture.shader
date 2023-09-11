#shader vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in float texIndex;

//获取纹理下标
out float v_TexIndex;
//输出该点对应的纹理坐标
out vec2 v_TexCoord;
//变换矩阵
uniform mat4 u_MVP;

void main()
{
    gl_Position =u_MVP * position;
    v_TexCoord = texCoord;
    v_TexIndex = texIndex;
};

#shader fragment
#version 330 core

//输出的颜色
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in float v_TexIndex;

uniform vec4 u_Color;
uniform sampler2D u_Textures[2];

void main()
{
    //根据纹理和纹理坐标获取颜色
    vec4 texColor;
    if(int(v_TexIndex) == 1) texColor = texture(u_Textures[1],v_TexCoord);
    else texColor = texture(u_Textures[0],v_TexCoord);;
    color = texColor;
};

