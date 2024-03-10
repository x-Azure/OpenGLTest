#include <tests/Test.hpp>
#include <imgui/imgui.h>
namespace Tests
{
    TestMenu::TestMenu(Test *&currentTestPtr) : m_CurrentTest(currentTestPtr) {}
    void TestMenu::OnImguiRender()
    {
        for (auto &test : m_Tests)
        {
            if (ImGui::Button(test.first.c_str()))
            {
                m_CurrentTest = test.second();
            }
        }
    }
}