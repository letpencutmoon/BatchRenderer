/*
filename:Shader.cpp
author:south
update:23.08.24
*/

#include "Shader.h"
#include "GL/glew.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"


Shader::Shader(const std::string& filepath)
    :m_FilePath(filepath),m_RendererID(0)
{
    ShaderProgramSource source = ParseShader();
    m_RendererID = CreateShader(source.VetexShader, source.FragmentShader);
}

Shader::~Shader()
{
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
    GLCall(glUseProgram(m_RendererID));
}

void Shader::UnBind() const
{
    GLCall(glUseProgram(0));
}
int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCahe.count(name)) return m_UniformLocationCahe[name];
    GLCall(int location = glGetUniformLocation(m_RendererID,name.c_str()));
    if (location == -1) {
        //不使用统一变量就会出现这个警告，而不一定是真的没有
        std::cout<< "Warnig: Uniform '" << name << "' not existing";
    }
    m_UniformLocationCahe[name] = location;
    return location;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name),value));
}

void Shader::SetUniform1f(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name,float v0, float v1, float f0,float f1)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, f0, f1));
}

void Shader::SetUniformMat4f(const std::string& name,const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name),1,GL_FALSE,&matrix[0][0]));
}

//从文件中读取着色器
ShaderProgramSource Shader::ParseShader()
{
    //文件流
    std::ifstream stream(m_FilePath);
    //定义文件着色器类型
    enum ShaderType {
	NONE = -1,VERTEX = 0,FRAGMENT = 1
    };
    std::string line;
    //用于存储两种着色器文件流
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    //逐行读取
    while (getline(stream,line))
    {
	//根据文件判断是那种着色器
	if (line.find("#shader") != std::string::npos) {
	    if (line.find("vertex") != std::string::npos)
		type = ShaderType::VERTEX;
	    else if (line.find("fragment") != std::string::npos)
		type = ShaderType::FRAGMENT;
       }
	//根据着色器存储文件流
	else {
	    ss[(int)type] << line << '\n';
	}
    }
    return { ss[0].str(),ss[1].str() };
}

//用于创建着色器，返回着色器ID
unsigned int Shader::CompileShader(const std::string& source,unsigned int type)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    //指定着色器的源码
    glShaderSource(id,1,&src,nullptr);
    //编译指定着色器代码
    glCompileShader(id);

    //检验是否编译成功
    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS,&result);
    if (result == GL_FALSE )
    {
	//获取错误信息
	int length;
	glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
	char* message= (char*)alloca(length * sizeof(char));
	glGetShaderInfoLog(id,length,&length,message);
	std::cout << "Falid Compile" << "\n";
	std::cout << message << "\n";
	glDeleteShader(id);
	return 0;
    }
    return id;
}

//将着色器源码作为string传入
unsigned int Shader::CreateShader(const std::string& vertexShader,const std::string& fragmentShader)
{
    //创建一个OpenGL程序
    unsigned int program = glCreateProgram();
    //创建两种顶点着色器
    unsigned int vs = CompileShader(vertexShader,GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentShader,GL_FRAGMENT_SHADER);
    //将着色器代码添加到程序中
    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);
    
    //得到目标程序，删除中间着色器
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
