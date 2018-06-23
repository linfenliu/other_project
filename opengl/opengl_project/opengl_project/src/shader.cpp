#include "shader.h"

#include <glad\glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

static std::string LoadFile(const std::string& path)
{
	std::ifstream ifs(path);

	if (ifs.is_open())
	{
		std::stringstream ss;
		ss << ifs.rdbuf();
		ifs.close();

		return std::string(ss.str());
	}
	
	std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;

	return std::string();

}

static int CreateSharder(const char* code, int mode)
{
	int shader = glCreateShader(mode);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);
	
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	return shader;
}

static int CreateShader(int vs, int fs)
{
	int prog = glCreateProgram();
	glAttachShader(prog, vs);
	glAttachShader(prog, fs);
	glLinkProgram(prog);
	
	int success;
	char infoLog[512];
	glGetProgramiv(prog, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(prog, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	return prog;
}

static void DeleteShader(int sharder)
{
	glDeleteShader(sharder);
}

Shader::Shader(const std::string& vertex_shader_source, const std::string& fragment_shader_source)
{
	const char* v_code = LoadFile(vertex_shader_source).c_str();
	const char* f_code = LoadFile(fragment_shader_source).c_str();

	int vertex_shader = CreateSharder(v_code, GL_VERTEX_SHADER);
	int fragment_shader = CreateSharder(f_code, GL_FRAGMENT_SHADER);

	ID = CreateShader(vertex_shader, fragment_shader);

	DeleteShader(vertex_shader);
	DeleteShader(fragment_shader);
}

void Shader::UseProgram()
{
	glUseProgram(ID);
}


void Shader::setBool(const std::string &name, bool value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string &name, int value)
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value)
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}