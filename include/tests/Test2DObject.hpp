#include "Test.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Renderer.hpp"
#include <memory>
namespace Tests
{
    struct TestObjs
    {
        std::string name;
        float color[4];
        glm::vec3 translation;
        TestObjs(std::string name, float n) : name(name), color{n, n, n, n}, translation(n, n, n){};
    };

    class Test2DObject : public Test
    {
    private:
        glm::mat4 m_View;
        glm::mat4 m_Proj;
        std::unique_ptr<VertexArray> m_va;
        std::unique_ptr<VertexBuffer> m_vb;
        std::unique_ptr<IndexBuffer> m_ib;
        std::unique_ptr<Shader> m_shader;
        TestObjs m_Objs[2];

    public:
        Test2DObject();
        ~Test2DObject();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImguiRender() override;
    };
}
