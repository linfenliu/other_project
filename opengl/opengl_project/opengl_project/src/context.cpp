#include "context.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <stb_image.h>

#include "shape.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::mat4 project_matrix;
float i = 0.0f;

Context::Context() :bRedraw(true), bVexColor(false), bTexture(false), alpha(0.0f)
{
	vertex_shader_source =  "\
					#version 330 core\n	\
					layout(location = 0) in vec3 aPos;\n	\
					void main()\n	\
					{\n	\
						gl_Position = vec4(aPos, 1.0);\n	\
					}";


	fragment_shader_source =  "\
					  #version 330 core\n	\
					  out vec4 FragColor; \n	\
					  void main()\n	\
					  {\n	\
						FragColor = vec4(0.7f,0.7f,0.7f,0.7f); \n	\
					  }";
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Context::InitGlfw()
{
	if (!::glfwInit())
	{
		std::cout << "Failed to initialize GLFW... " << std::endl;
	}
}

void Context::InitGlfwVersion(int32_t major, int32_t minor, int32_t mode)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);

	switch (mode)
	{
	case 0:
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
		break;
	case 1:
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		break;
	case 2:
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
		break;
	default:
		break;
	}
}

void Context::CreateBindWindow(int width, int height, const char* title)
{
	pwindow = ::glfwCreateWindow(width, height, title, nullptr, nullptr);

	if (!pwindow)
	{
		std::cout << "Failed to create GLFW window... " << std::endl;
	}

	::glfwMakeContextCurrent(pwindow);
}

void Context::SetViewPort(int lo_0, int lo_1, int hi_0, int hi_1)
{
	::glViewport(lo_0, lo_1, hi_0, hi_1);
}

void Context::InitGlad()
{
	if (!::gladLoadGLLoader((GLADloadproc)::glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD... " << std::endl;
	}
}

void Context::FixWindow()
{
	::glfwSetFramebufferSizeCallback(pwindow, framebuffer_size_callback);
}

static void processInput(GLFWwindow *window, float& alpha)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		--i;
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		++i;
	}
	
	//if any key or mouse or window event happen, set bRedraw flag to true...

}

void Context::SetBackGroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	bgcolor.SetColor(r, g, b, a);
}

void Context::SetBackGroundColor(const Color& c)
{
	bgcolor = c;
}

void Context::SetShapeColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	shpcolor.SetColor(r, g, b, a);
}

void Context::SetShapeColor(const Color& c)
{
	shpcolor = c;
}

void Context::RenderLoop(Shape& shp)
{
	do 
	{
		processInput(pwindow, alpha);
		
		if (bRedraw)
		{
			::glClearColor(bgcolor[0] / 255.0f, bgcolor[1] / 255.0f, bgcolor[2] / 255.0f, bgcolor[3] / 255.0f);
			::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			shp.DoRender(*this);
			::glfwSwapBuffers(pwindow);
			bRedraw = false;
		}
		
		::glfwPollEvents();
	} 
	while ((!::glfwWindowShouldClose(pwindow)));
}

void Context::Release()
{
	::glfwTerminate();
}

void Context::Begin()
{
	vertexs.clear();
	indexs.clear();
	
}

void Context::Vertexs(const vec3d& v)
{
	vertexs.push_back(v);
}

void Context::VertexColors(const Color& c)
{
	vertexs.push_back(vec3f(c[0] / 255.0f, c[1] / 255.0f, c[2] / 255.0f, c[3] / 255.0f));
	bVexColor = true;
}

void Context::VertexTexture(const vec2d& v)
{
	vertexs.push_back(vec3f((float)v[0], (float)v[1], (float)0.0));
	bTexture = true;
}

void Context::Indexs(unsigned int n)
{
	indexs.push_back(n);
}

void Context::VertexShaderSource(const std::string& s)
{
	vertex_shader_source = s;
}

void Context::FragmentShaderSource(const std::string& s)
{
	fragment_shader_source = s;
}

static int SendVAO2GPU(const std::vector<vec3f>& d, const std::vector<unsigned int>& idx, bool bVexColor, bool bTexture)
{
	unsigned int VAO;
	::glGenVertexArrays(1, &VAO);
	::glBindVertexArray(VAO);
	
	unsigned int VBO;
	::glGenBuffers(1, &VBO);
	::glBindBuffer(GL_ARRAY_BUFFER, VBO);
	::glBufferData(GL_ARRAY_BUFFER, d.size()*sizeof(vec3f), d.data(), GL_STATIC_DRAW);

	if (!idx.empty())
	{
		unsigned int EBO;
		glGenBuffers(1, &EBO);
		::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * idx.size(), idx.data(), GL_STATIC_DRAW);
	}

	if (!bVexColor && !bTexture)
	{
		::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		::glEnableVertexAttribArray(0);
	}
	else if (bVexColor && !bTexture)
	{
		::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		::glEnableVertexAttribArray(0);

		::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		::glEnableVertexAttribArray(1);
	}
	else if (bVexColor && bTexture)
	{
		::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
		::glEnableVertexAttribArray(0);

		::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		::glEnableVertexAttribArray(1);

		::glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
		::glEnableVertexAttribArray(2);
	}
	
	return VAO;
}

static int CreateSharder(const char* s, int32_t type)
{
	unsigned int vertex_shader = ::glCreateShader(type);
	::glShaderSource(vertex_shader, 1, &s, NULL);
	::glCompileShader(vertex_shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return vertex_shader;
}

static int CreateProgram(int vs, int fs)
{
	unsigned int shader_program = ::glCreateProgram();

	::glAttachShader(shader_program, vs);
	::glAttachShader(shader_program, fs);
	::glLinkProgram(shader_program);
	::glDeleteShader(vs);
	::glDeleteShader(fs);

	int success;
	char infoLog[512];
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	return shader_program;
}

static void SetUniformShpColor(const Color& c ,int32_t prog, float alpha)
{
	int vertex_color_location = ::glGetUniformLocation(prog, "our_color");
	::glUniform4f(vertex_color_location, c[0] / 255.0f, c[1] / 255.0f, c[2] / 255.0f, c[3] / 255.0f);

	int alpha_prog = ::glGetUniformLocation(prog, "alpha");
	::glUniform1f(alpha_prog, alpha);


	glm::mat4 trsf = glm::scale(glm::mat4(), glm::vec3(0.5f, 0.5f, 0.5f));
	trsf = glm::rotate(trsf, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	//trsf = glm::translate(trsf, glm::vec3(1.0f, 0.0f, 0.0f));
	int matrix = ::glGetUniformLocation(prog, "matrix");
	::glUniformMatrix4fv(matrix, 1, GL_FALSE, glm::value_ptr(trsf));
}

static unsigned int LoadTexture(const std::string& path)
{
	unsigned int texture0;
	glGenTextures(1, &texture0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	{
		unsigned int texture1;
		glGenTextures(1, &texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		data = stbi_load("4.png", &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}


	return texture0;
}

void Context::End()
{
	project_matrix = glm::scale(glm::mat4(), glm::vec3(1.0f / 2000.0f, 1.0f / 1200.0f, 1.0f / 3000.0f));
	glm::mat4 view_matrix = glm::translate(glm::mat4(), glm::vec3(0.0f, (3000.0f / 100.0f) * i, 0.0f));
	glm::mat4 model_matrix = glm::rotate(glm::mat4(), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));


	int vs = CreateSharder(vertex_shader_source.c_str(), GL_VERTEX_SHADER);
	int fs = CreateSharder(fragment_shader_source.c_str(), GL_FRAGMENT_SHADER);
	int prog = CreateProgram(vs, fs);
	::glUseProgram(prog);

	SetUniformShpColor(shpcolor, prog, alpha);
	if (bTexture)
	{
		LoadTexture(texture_path);
	}

	glUniform1i(glGetUniformLocation(prog, "texture0"), 0);
	glUniform1i(glGetUniformLocation(prog, "texture1"), 1);

	glUniformMatrix4fv(glGetUniformLocation(prog, "project_martix"), 1, GL_FALSE, glm::value_ptr(project_matrix));
	glUniformMatrix4fv(glGetUniformLocation(prog, "view_martix"), 1, GL_FALSE, glm::value_ptr(view_matrix));
	glUniformMatrix4fv(glGetUniformLocation(prog, "model_martix"), 1,GL_FALSE , glm::value_ptr(model_matrix));


	int vao = SendVAO2GPU(vertexs, indexs, bVexColor, bTexture);
	::glBindVertexArray(vao);

	if (indexs.empty())
	{
		::glDrawArrays(GL_TRIANGLES, 0, vertexs.size());
	}
	else
	{
		::glDrawElements(GL_TRIANGLES, indexs.size(), GL_UNSIGNED_INT, 0);
	}

	vertexs.clear();
	indexs.clear();
	
}


void Context::Commit()
{}


void Context::SetTexture(const std::string& path)
{
	texture_path = path;
}
