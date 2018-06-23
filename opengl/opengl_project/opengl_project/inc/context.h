#ifndef FL_CONTEXT_H
#define FL_CONTEXT_H

#include <inttypes.h>

#include <vector>
#include <string>

#include "color.h"
#include "vec3d.h"

struct GLFWwindow;
class Shape;


class Context
{
public:

	Context();

	GLFWwindow* GetCurrentWindow()
	{
		return pwindow;
	}

	void InitGlfw();
	void InitGlfwVersion(int32_t major, int32_t minor, int32_t mode);

	void CreateBindWindow(int width, int height, const char* title);
	void SetViewPort(int lo_0, int lo_1, int hi_0, int hi_1);

	void InitGlad();

	void FixWindow();

	void RenderLoop(Shape& shp);

	void Release();

	void SetBackGroundColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void SetBackGroundColor(const Color& c);

	void SetShapeColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	void SetShapeColor(const Color& c);

	void Begin();
	void End();
	void Commit();

	void Vertexs(const vec3d& v);
	void VertexColors(const Color& c);
	void Indexs(unsigned int n);

	void VertexShaderSource(const std::string& s);
	void FragmentShaderSource(const std::string& s);

private:
	GLFWwindow* pwindow;
	Color bgcolor;
	Color shpcolor;

	std::vector<vec3f> vertexs;
	std::vector<unsigned int> indexs;

	std::string vertex_shader_source;
	std::string fragment_shader_source;

	bool bRedraw;
	bool bVexColor;
};


#endif