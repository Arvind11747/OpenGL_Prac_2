//#ifndef SHADER_H
//#define SHADER_H
#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

struct ShaderProgram
{
	std::string vertexCode;
	std::string fragmentCode;
};

class Shader
{
private:
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);

	void Bind() const;
	void Unbind() const;

	void SetBool(const std::string& name, bool value);
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform3f(const std::string& name, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, glm::mat4& value);
	~Shader();

private:
	ShaderProgram ParseShader(const char* vertexShaderPath, const char* fragmentShaderPath);
	unsigned int CompileShader(const unsigned int shaderType, const char* shaderSource);
	unsigned int CreateShader(ShaderProgram shaderCode);

	int GetUniformLocation(const std::string& name);
};


//#endif