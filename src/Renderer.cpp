#include <Renderer.hpp>
void Renderer::Clear() const
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
void Renderer::Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const
{
    va.Bind();
    ib.Bind();
    shader.Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}