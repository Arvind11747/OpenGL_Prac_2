#include <glad/glad.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"


Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) : m_RendererID(0)
{
	ShaderProgram shaderCode = ParseShader(vertexShaderPath, fragmentShaderPath);
	m_RendererID = CreateShader(shaderCode);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
	m_UniformLocationCache.clear();
}

ShaderProgram Shader::ParseShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	// 1. Retrieve the vertex/fragment source code from filePath.
	ShaderProgram shaderCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//Ensure ifStream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//open
		vShaderFile.open(vertexShaderPath);
		fShaderFile.open(fragmentShaderPath);
		//read files' buffer content into streams
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//close file handlers
		vShaderFile.close();
		fShaderFile.close();
		//convert stream info string.
		shaderCode.vertexCode = vShaderStream.str();
		shaderCode.fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "Error shader file not successfully read" << std::endl;
	}
	return shaderCode;
}

unsigned int Shader::CreateShader(ShaderProgram shaderCode)
{
	const char* vertexShader = shaderCode.vertexCode.c_str();
	const char* fragmentShader = shaderCode.fragmentCode.c_str();

	unsigned int program = glCreateProgram();
	unsigned int vertex = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fragment = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	int success;
	char infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "Error shader linking program failed\n" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glUseProgram(0);
	return program;
}

unsigned int Shader::CompileShader(const unsigned int shaderType, const char* shaderSource)
{
	unsigned int shaderID;
	int success;
	char infoLog[512];

	shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderSource, NULL);
	glCompileShader(shaderID);

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::string ShaderDetail = shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment "; //Temp
		std::cout << "Error shader " << ShaderDetail << " compilation failed\n " << infoLog << std::endl;
		glDeleteShader(shaderID);
		return 0;
	}
	return shaderID;
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}
	int location = glGetUniformLocation(m_RendererID, name.c_str());

	if (location == -1)
	{
		std::cout << "Uniform: " << name << " doesn't exist, Check the name in the program or the shader!" << std::endl;
	}
	m_UniformLocationCache[name] = location;
	return location;
}

void Shader::SetBool(const std::string& name, bool value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetUniform3f(const std::string& name, float v1, float v2, float v3)
{
	glUniform3f(GetUniformLocation(name), v1, v2, v3);
}
void Shader::SetUniformMat4f(const std::string& name, glm::mat4& value)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &value[0][0]);
}
