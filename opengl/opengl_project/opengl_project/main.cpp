#include "inc\context.h"
#include <iostream>

#include "shape.h"

static void InitOpenGl(Context& ctx)
{
	ctx.InitGlfw();
	ctx.InitGlfwVersion(3, 3, 1);

	ctx.CreateBindWindow(2000, 1200, "OpenGL");

	ctx.InitGlad();
	ctx.SetViewPort(0, 0, 2000, 1200);

	ctx.FixWindow();

	ctx.SetBackGroundColor(200, 200, 200, 255);
}

int main(size_t argc, char* argv[])
{
	Context ctx;

	ShapeRectangle shp;

	InitOpenGl(ctx);


	ctx.RenderLoop(shp);

	ctx.Release();

	return 0;
}