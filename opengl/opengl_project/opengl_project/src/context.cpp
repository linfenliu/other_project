#include "context.h"

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

#include "shape.h"

Context::Context() :bRedraw(true), bVexColor(false)
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

static void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
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
		processInput(pwindow);

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

static int SendVAO2GPU(const std::vector<vec3f>& d, const std::vector<unsigned int>& idx, bool bVexColor)
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

	if (!bVexColor)
	{
		::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		::glEnableVertexAttribArray(0);
	}
	else
	{
		::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		::glEnableVertexAttribArray(0);

		::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		::glEnableVertexAttribArray(1);
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

static void SetUniformShpColor(const Color& c ,int32_t prog)
{
	int vertex_color_location = ::glGetUniformLocation(prog, "our_color");
	::glUniform4f(vertex_color_location, c[0] / 255.0f, c[1] / 255.0f, c[2] / 255.0f, c[3] / 255.0f);
	
}

void Context::End()
{
	int vs = CreateSharder(vertex_shader_source.c_str(), GL_VERTEX_SHADER);
	int fs = CreateSharder(fragment_shader_source.c_str(), GL_FRAGMENT_SHADER);
	int prog = CreateProgram(vs, fs);
	::glUseProgram(prog);
	SetUniformShpColor(shpcolor, prog);


	int vao = SendVAO2GPU(vertexs, indexs, bVexColor);
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
{
	
}
