#include "Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	ShaderCode shaderCode = ReadShader(vertexShaderPath, fragmentShaderPath);
	const char* vShaderCode = shaderCode.vertexCode.c_str();
	const char* fShaderCode = shaderCode.fragmentCode.c_str();
	unsigned int vertex, fragment;

	vertex = CompileShader(GL_VERTEX_SHADER, vShaderCode);
	fragment = CompileShader(GL_FRAGMENT_SHADER, fShaderCode);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	int success;
	char infoLog[512];

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Error shader linking program failed\n" << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glUseProgram(0);
}

ShaderCode Shader::ReadShader(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	// 1. Retrieve the vertex/fragment source code from filePath.
	ShaderCode shaderCode;
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

unsigned int Shader::CompileShader(GLuint shaderType, const char* shaderSource)
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
	}
	return shaderID;
}

void Shader::UseShader()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setUniformfv(const std::string& name, float v1, float v2, float v3) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), v1, v2, v3);
}

Shader::~Shader()
{
}

