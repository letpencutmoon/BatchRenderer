/*
filename:TestRectangle.cpp
author: south
update:2023.9.5
*/

#include "Renderer.h"
#include "imgui/imgui.h"
#include "VertexBufferLayout.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image/stb_image.h"
#include "TestRectangle.h"

namespace test
{
    test::TestRectangle::TestRectangle()
    {
        float points[] = 
        {
            -200.0f,-200.0f,
            200.0f,-200.0f,
            200.0f,200.0f,
            -200.0f,200.0f,

            -100.0f,-100.0f,
            -100.0f,300.0f,
            300.0f,300.0f,
            300.0f,-100.0f
        };

        unsigned int indices[] = 
        {
            0,1,2,
            2,3,0,
            
            4,5,6,
            6,7,4
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        m_Shader = std::make_unique<Shader>("/home/south/graphics/opengl/batchrenderer/res/shaders/Rectangle.shader");
        m_VAO = std::make_unique<VertexArray>();
        m_VBO = std::make_unique<VertexBuffer>(points, sizeof(points));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        m_VAO->AddBuffer(*m_VBO, layout);
        m_IBO = std::make_unique<IndexBuffer>(indices, 12);
        m_proj = glm::ortho(-480.0f, 480.0f, -360.0f, 360.0f, -1.0f, 1.0f);
        m_view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        m_VBO->Unbind();
        m_VAO->UnBind();
        m_IBO->Unbind();
        m_Shader->UnBind();
    }

    test::TestRectangle::~TestRectangle()
    {
    }

    void test::TestRectangle::OnUpdate(float deltaTime)
    {
    }

    void test::TestRectangle::OnRender()
    {
        GLCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Renderer renderer;

        m_VAO->Bind();
        m_IBO->Bind();

        {
            // glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
            glm::mat4 mvp = m_proj * m_view;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP",mvp);
            renderer.Draw(*m_VAO,*m_IBO,*m_Shader);
        }
    }

    void test::TestRectangle::OnImGuiRender()
    {
        return;
    }
}