#include "shape.h"

#include "context.h"



void ShapeTriangle::DoRender(Context& ctx)
{
	basetype::DoRender(ctx);

	ctx.Begin();

	ctx.Vertexs(vec3d(-0.5, -0.5, 0.0));
	ctx.Vertexs(vec3d(0.5, -0.5, 0.0));
	ctx.Vertexs(vec3d(0.0, 0.5, 0.0));

	ctx.Vertexs(vec3d(0.5, -0.5, 0.0));
	ctx.Vertexs(vec3d(0.0, -1.0, 0.0));
	ctx.Vertexs(vec3d(-0.5, -0.5, 0.0));
	

	ctx.End();

	ctx.Commit();
}

void ShapeRectangle::DoRender(Context& ctx)
{
	basetype::DoRender(ctx);

	ctx.Begin();

	ctx.Vertexs(vec3d(0.5, 0.5, 0.0));
	ctx.Vertexs(vec3d(0.5, -0.5, 0.0));
	ctx.Vertexs(vec3d(-0.5, -0.5, 0.0));
	ctx.Vertexs(vec3d(-0.5, 0.5, 0.0));

	ctx.Indexs(0);
	ctx.Indexs(1);
	ctx.Indexs(3);
	ctx.Indexs(1);
	ctx.Indexs(2);
	ctx.Indexs(3);

	ctx.End();

	ctx.Commit();
}









ShapeCube::ShapeCube() :width(vec3d(10.0, 10.0, 10.0)), center(vec3d(0.0,0.0,0.0))
{}

void ShapeCube::SetWidth(const vec3d& wid)
{
	width = wid;
}

void ShapeCube::SetCenter(const vec3d& cen)
{
	center = cen;
}

void ShapeCube::DoRender(Context& ctx)
{
	basetype::DoRender(ctx);


}

