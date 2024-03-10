#pragma once
#include "Test.hpp"
namespace Tests
{
    class TestClearColor : public Test
    {
    public:
        TestClearColor();
        ~TestClearColor();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;

    private:
        float m_ClearColor[4];
    };
}
