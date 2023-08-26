/*
filename:Application.cpp
author:south
*/
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "TestClearColor.h"
#include "TestTexture2D.h"



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
	return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(960, 680, "Hello World", NULL, NULL);
    //设置帧率
    glfwSwapInterval(1);
    if (!window)
    {
	glfwTerminate();
	return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //初始化glew，用于使用现代OpenGL和扩展
    if (glewInit() != GLEW_OK)
    {
	std::cout << "glew Init Error\n";
    }
    std::cout << glGetString(GL_VERSION) << '\n';
    {
    //启用混合
    GLCall(glEnable(GL_BLEND));
    //定义如何混合alpha像素
    GLCall(glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA));

    Renderer renderer;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    const char* glsl_version = "#version 330";

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); 
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    test::Test* currentTest = NULL;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<test::TestClearColor>("Clear Color");
    testMenu->RegisterTest<test::TestTexture2D>("2D Texture");

    while (!glfwWindowShouldClose(window))
    {
	/* Render here */
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        renderer.Clear();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        if (currentTest)
        {
            currentTest->OnUpdate(0.0f);
            currentTest->OnRender();
            ImGui::Begin("Test");
            if (currentTest != testMenu && ImGui::Button("<-"))
            {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->OnImGuiRender();
            ImGui::End();
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	/* Swap front and back buffers */
	glfwSwapBuffers(window);
       /* Poll for and process events */
	glfwPollEvents();
    }


    delete currentTest;
    if(currentTest != testMenu) delete testMenu;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);

    glfwTerminate();
    return 0;
}