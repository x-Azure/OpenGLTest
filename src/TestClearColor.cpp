#include "tests/TestClearColor.hpp"
#include <GL/glew.h>
#include <imgui/imgui.h>
#include <Renderer.hpp>
namespace Tests
{

    TestClearColor::TestClearColor() : m_ClearColor{0.2f, 0.3f, 0.8f, 1.0f}
    {
    }

    TestClearColor::~TestClearColor()
    {
    }
    void TestClearColor::OnUpdate(float deltaTime)
    {
    }

    void TestClearColor::OnRender()
    {
        glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void TestClearColor::OnImguiRender()
    {
        ImGui::ColorEdit4("ClearColor", m_ClearColor);
    }
}