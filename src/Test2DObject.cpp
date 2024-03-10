#include <tests/Test2DObject.hpp>
#include <imgui/imgui.h>
#include <Renderer.hpp>
namespace Tests
{
    Test2DObject::Test2DObject() : m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0))),
                                   m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
                                   m_Objs{{"Obj1", 0.8f}, {"Obj2", 0.8f}}
    {
        float positions[] = {
            -50.0f, -50.0f,
            50.0f, -50.0f,
            50.0f, 50.0f,
            -50.0f, 50.0f};
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0};
        m_va = std::make_unique<VertexArray>();
        m_vb = std::make_unique<VertexBuffer>(positions, sizeof(positions));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        m_va->AddBuffer(*m_vb, layout);
        m_ib = std::make_unique<IndexBuffer>(indices, 6);
        m_shader = std::make_unique<Shader>("res/shader/2dObj.shader");
    }

    Test2DObject::~Test2DObject()
    {
    }
    void Test2DObject::OnRender()
    {
        Renderer render;
        int j = 0;
        for (int i = 0; i < sizeof(m_Objs) / sizeof(TestObjs); i++)
        {
            m_shader->Bind();
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_Objs[i].translation);
            glm::mat4 MVP = m_Proj * m_View * model;

            m_shader->SetUniform4f("u_Color", m_Objs[i].color[0], m_Objs[i].color[1], m_Objs[i].color[2], m_Objs[i].color[3]);

            m_shader->SetUniformMat4f("u_MVP", MVP);
            render.Draw(*m_va, *m_ib, *m_shader);
            j += 110;
        }
    };
    void Test2DObject::OnUpdate(float deltaTime) {}
    void Test2DObject::OnImguiRender()
    {
        for (int i = 0; i < sizeof(m_Objs) / sizeof(TestObjs); i++)
        {
            ImGui::SliderFloat3(m_Objs[i].name.c_str(), &m_Objs[i].translation.x, 0, 1000);
            ImGui::ColorEdit4(m_Objs[i].name.c_str(), m_Objs[i].color);
        }
    }
}