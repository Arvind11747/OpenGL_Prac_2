#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct ShaderCode
{
	std::string vertexCode;
	std::string fragmentCode;
};

class Shader
{
public:
	unsigned int ID;

	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);

	ShaderCode ReadShader(const char* vertexShaderPath, const char* fragmentShaderPath);
	unsigned int CompileShader(GLuint shaderType, const char* shaderSource);
	void UseShader();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setUniformfv(const std::string& name, float v1, float v2, float v3) const;
	~Shader();

private:

};


#endif