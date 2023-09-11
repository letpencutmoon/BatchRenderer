/*
filename:TestTectangle.h
author:south
update:2023.9.5
*/

#include "Test.h"
#include <memory>


namespace test
{
    class TestRectangle: public Test
    {
    public:
        TestRectangle();
        ~TestRectangle();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        // /// @brief 一个矩形左上角的X坐标
        // float m_X;
        // /// @brief 一个矩形左上角的Y坐标
        // float m_Y;
        // /// @brief 矩形的宽
        // float m_Width;
        // /// @brief 矩形的长
        // float m_Height;

        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<IndexBuffer> m_IBO;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<VertexBuffer> m_VBO;
        glm::mat4 m_proj;
        glm::mat4 m_view;
    };
}