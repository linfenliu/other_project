#include "shape.h"

#include "context.h"

#include <ctime>



void ShapeTriangle::DoRender(Context& ctx)
{
	basetype::DoRender(ctx);

	ctx.Begin();

	ctx.Vertexs(vec3d(-0.5, -0.5, 0.0));
	ctx.VertexColors(Color(255, 0, 0));
	ctx.Vertexs(vec3d(0.5, -0.5, 0.0));
	ctx.VertexColors(Color(0, 255, 0));
	ctx.Vertexs(vec3d(0.0, 0.5, 0.0));
	ctx.VertexColors(Color(0, 0, 255));


	std::string vs = "\
					#version 330 core\n \
					layout (location = 0) in vec3 aPos;\n	\
					layout (location = 1) in vec3 aColor;\n	\
					out vec3 our_color;\n	\
					void main(){\n	\
						gl_Position = vec4(aPos, 1.0);\n	\
						our_color = aColor;\n	\
					}\n \
					";
	ctx.VertexShaderSource(vs);

	std::string fs = "	\
		#version 330 core\n	\
		out vec4 FragColor;\n	\
		in vec3 our_color;\n	\
		void main()\n	\
		{\n	\
		    FragColor = vec4(our_color, 1.0);\n	\
		}";

	ctx.FragmentShaderSource(fs);

	ctx.End();

	ctx.Commit();
}

void ShapeRectangle::DoRender(Context& ctx)
{
	basetype::DoRender(ctx);


	ctx.Vertexs(vec3d(500, 500, 0.0));
	ctx.VertexColors(Color(255, 0, 0));
	ctx.VertexTexture(vec2d(1.0, 1.0));
	
	ctx.Vertexs(vec3d(500, -500, 0.0));
	ctx.VertexColors(Color(0, 255, 0));
	ctx.VertexTexture(vec2d(1.0, 0.0));
	
	ctx.Vertexs(vec3d(-500, -500, 0.0));
	ctx.VertexColors(Color(0, 0, 255));
	ctx.VertexTexture(vec2d(0.0, 0.0));

	ctx.Vertexs(vec3d(-500, 500, 0.0));
	ctx.VertexColors(Color(255,255,0));
	ctx.VertexTexture(vec2d(0.0, 1.0));
	
	ctx.Indexs(0);
	ctx.Indexs(3);
	ctx.Indexs(1);
	ctx.Indexs(3);
	ctx.Indexs(2);
	ctx.Indexs(1);

	std::string vs = "\
					#version 330 core\n \
					layout (location = 0) in vec3 aPos;\n	\
					layout (location = 1) in vec3 aColor;\n	\
					layout (location = 2) in vec3 aTexCord;\n	\
					out vec3 our_color;\n	\
					out vec2 our_tex;\n\
					out vec2 our_tex1; \n\
					uniform mat4 project_martix; \n\
					uniform mat4 view_martix; \n\
					uniform mat4 model_martix; \n\
					void main(){\n	\
						gl_Position = project_martix * view_martix * model_martix * vec4(aPos, 1.0);\n	\
						our_color = aColor;\n	\
						our_tex = vec2(aTexCord.xy); \n\
						if(our_tex.x == 0.0f){our_tex1.x = 1.0f;our_tex1.y = our_tex.y;}else if(our_tex.x == 1.0f){our_tex1.x = 0.0f;our_tex1.y = our_tex.y;};\n	\
					}\n \
					";
	ctx.VertexShaderSource(vs);

	std::string fs = "	\
		#version 330 core\n	\
		out vec4 FragColor;\n	\
		in vec3 our_color;\n	\
		in vec2 our_tex;\n\
		in vec2 our_tex1;\n\
		uniform float alpha;\n\
		uniform sampler2D texture0;\n\
		uniform sampler2D texture1;\n\
		void main()\n	\
		{\n	\
			FragColor =  mix(texture(texture0, our_tex), texture(texture1, our_tex1), alpha) ;\n	\
		}";
	//*vec4(our_color,1.0)
	ctx.FragmentShaderSource(fs);
	ctx.SetTexture("1.jpg");

	ctx.End();

	ctx.Commit();
}









ShapeCube::ShapeCube() :width(vec3d(10.0, 10.0, 10.0)), center(vec3d(0.0, 0.0, 0.0))
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

