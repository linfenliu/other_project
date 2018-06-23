#ifndef FLEW_SHAPE_H
#define FLEW_SHAPE_H

#include "vec3d.h"

class Context;

class Shape
{
public:
	virtual void DoRender(Context& ctx){}
};


class ShapeTriangle : public Shape
{
public:
	typedef Shape basetype;

	virtual void DoRender(Context& ctx);
};

class ShapeRectangle : public Shape
{
public:
	typedef Shape basetype;

	virtual void DoRender(Context& ctx);
};


class ShapeCube : public Shape
{
public:
	typedef Shape basetype;

	ShapeCube();

	virtual void DoRender(Context& ctx);

	void SetWidth(const vec3d& wid);
	void SetCenter(const vec3d& cen);

protected:
	vec3d width;
	vec3d center;
};



#endif