/*
filename:TestClearColor.cpp
author:south
*/
#include "TestTexture2D.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image/stb_image.h"
namespace test
{
    test::TestTexture2D::TestTexture2D()
        :m_TranslationA(200,100,0),m_TranslationB(100,50,0)
    {
        float points[] =
        {
        -200.0f,-100.0f,0.0f,0.0f, //0
        200.0f,-100.0f, 1.0f,0.0f,//1
        200.0f,100.0f, 1.0f,1.0f,//2
        -200.0f,100.0f , 0.0f,1.0f//3
        };
        unsigned int indices[] =
        {
            0,1,2,
            2,3,0
        };

        //启用混合,定义如何混合像素
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_Shader = std::make_unique<Shader>("/home/south/graphics/opengl/batchrenderer/res/shaders/Texture.shader");
        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(points, sizeof(points));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VBO, layout);

        m_IBO = std::make_unique<IndexBuffer>(indices, 6);

        //生成正交矩阵,定义视图空间的大小，超过这个大小的物体不会显示
        m_proj = glm::ortho(-480.0f, 480.0f, -360.0f, 360.0f, -1.0f, 1.0f);
        //定义一个平移变换，将图形向左平移100
        m_view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));

        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        //设置纹理,插槽
        m_Texture = std::make_unique<Texture>("/home/south/graphics/opengl/batchrenderer/res/texture/eriko.png");
        m_Shader->SetUniform1i("u_Texture", 0);

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
        m_Texture->Bind();

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_proj * m_view * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(*m_VAO, *m_IBO, *m_Shader);
        }
        
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
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
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    }
}


