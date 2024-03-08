#pragma once
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
class VertexArray
{
private:
    unsigned int m_RendererID;

public:
    VertexArray();
    ~VertexArray();
    void Bind() const;
    void UnBind() const;
    void AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout);
};