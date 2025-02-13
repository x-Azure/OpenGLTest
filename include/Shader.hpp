#pragma once
#include <unordered_map>
#include <iostream>
#include <glm/glm.hpp>
struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};
class Shader
{
private:
    unsigned int m_RendererID;
    std::string m_Filepath;
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
    Shader(const std::string &filepath);
    ~Shader();
    void SetUniform1i(const std::string &name, int v0);

    void SetUniform1f(const std::string &name, float v0);

    void SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3);

    void SetUniformMat4f(const std::string &name, const glm::mat4 matrix);

    void Bind() const;
    void UnBind() const;

private:
    ShaderProgramSource ParseShader(const std::string &filepath);
    unsigned int CompileShader(unsigned int type, const std::string &source);
    unsigned int CreateShader(const std::string &vertexShader, const std::string &fragmentShader);
    int GetUniformLocation(const std::string &name);
};