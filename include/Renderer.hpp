#pragma once
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader) const;
};