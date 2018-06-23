#include "inc\context.h"
#include <iostream>

#include "shape.h"

static void InitOpenGl(Context& ctx)
{
	ctx.InitGlfw();
	ctx.InitGlfwVersion(3, 3, 1);

	ctx.CreateBindWindow(1024, 860, "OpenGL");

	ctx.InitGlad();
	ctx.SetViewPort(0, 0, 1024, 860);

	ctx.FixWindow();

	ctx.SetBackGroundColor(200, 200, 200, 255);
}

int main(size_t argc, char* argv[])
{
	Context ctx;

	ShapeTriangle triangle;

	InitOpenGl(ctx);

	ctx.RenderLoop(triangle);

	ctx.Release();

	return 0;
}