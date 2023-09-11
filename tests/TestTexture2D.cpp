/*
filename:TestClearColor.cpp
author:south
*/
#include "TestTexture2D.h"
#include "../Renderer.h"
#include "imgui/imgui.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image/stb_image.h"
#include <vector>

namespace test
{
test::TestTexture2D::TestTexture2D()
    :m_TranslationA(0,0,0),m_TranslationB(0,0,0)
    {

    std::vector<unsigned int> v_indices;

    for(unsigned int i=0;i< 4* 10;i+=4)
    {
        v_indices.push_back(i);
        v_indices.push_back(i+1);
        v_indices.push_back(i+2);

        v_indices.push_back(i+2);
        v_indices.push_back(i+3);
        v_indices.push_back(i);
    }
    //启用混合,定义如何混合像素
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    m_Shader = std::make_unique<Shader>("/home/south/graphics/opengl/batchrenderer/res/shaders/Texture.shader");

    VertexBufferLayout layout;
    layout.Push<float>(3);
    layout.Push<float>(2);
    layout.Push<float>(1);
    m_VAO = std::make_unique<VertexArray>(layout);

    for(int i = 0; i < 10;i++)
    {
        float l = -480.0f + i*100;
        float r = -480.0f + i*100 + 100;
        float d = -360.0f + i*60;
        float u = -360.0f + i*60 + 60;
        
        float textureIndex = float(i%2);
        float v1[] = {l,d,0.0f,0.0f,0.0f,textureIndex};
        float v2[] = {r,d,0.0f,1.0f,0.0f,textureIndex};
        float v3[] = {r,u,0.0f,1.0f,1.0f,textureIndex};
        float v4[] = {l,u,0.0f,0.0f,1.0f,textureIndex};
        m_VAO->AddBuffer(v1,sizeof(v1));
        m_VAO->AddBuffer(v2,sizeof(v1));
        m_VAO->AddBuffer(v3,sizeof(v1));
        m_VAO->AddBuffer(v4,sizeof(v1));
    }
    const unsigned int* indices = v_indices.data();
    m_IBO = std::make_unique<IndexBuffer>(indices, v_indices.size());

    //生成正交矩阵,定义视图空间的大小，超过这个大小的物体不会显示
    m_proj = glm::ortho(-480.0f, 480.0f, -360.0f, 360.0f, -1.0f, 1.0f);
    //定义一个平移变换，将图形向左平移0
    m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

    m_Shader->Bind();
    m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    //设置纹理,插槽
    m_Texture1 = std::make_unique<Texture>("/home/south/graphics/opengl/batchrenderer/res/texture/eriko.png");
    m_Texture2 = std::make_unique<Texture>("/home/south/graphics/opengl/batchrenderer/res/texture/miyako.png");
    int textures[] = {0,1};
    m_Shader->SetUniform1iv("u_Textures",2,textures);

    //解绑程序和缓冲区
    m_VAO->UnBind();
    m_VBO->Unbind();
    m_IBO->Unbind();
    m_Shader->UnBind();
}

test::TestTexture2D::~TestTexture2D()
{
}

void test::TestTexture2D::OnUpdate(float deltaTime)
{
}

void test::TestTexture2D::OnRender()
{
    GLCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    Renderer renderer;

    m_VAO->Bind();
    m_IBO->Bind();
    m_Texture1->Bind();
    m_Texture2->Bind(1);

    {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
        glm::mat4 mvp = m_proj * m_view * model;
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_MVP", mvp);
        renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
    }
}

void test::TestTexture2D::OnImGuiRender()
{
    ImGui::SliderFloat3("Translation A", &m_TranslationA.x, -480.0f, 480.0f);
    ImGui::SliderFloat3("Translation B", &m_TranslationB.x, -480.0f, 480.0f);
    ImGuiIO& io = ImGui::GetIO(); 
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;     
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
}
}


