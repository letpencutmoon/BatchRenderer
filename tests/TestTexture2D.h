/*
filename:TestClearColor.h
author:south
*/

#pragma once

#include <memory>
#include "Test.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Shader.h"


namespace test
{
    class TestTexture2D : public Test
    {
    public:
        TestTexture2D();
        ~TestTexture2D();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

    private:
        glm::vec3 m_TranslationA;
        glm::vec3 m_TranslationB;
        glm::mat4 m_proj;
        glm::mat4 m_view;

        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture1;
        std::unique_ptr<Texture> m_Texture2;
        std::unique_ptr<VertexBuffer> m_VBO;
    };
}
