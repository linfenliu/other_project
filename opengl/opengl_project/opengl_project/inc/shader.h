#ifndef FLEW_SHADER_H
#define FLEW_SHADER_H

#include <string>

class Shader
{
public:

	Shader(const std::string& vertex_shader_source, const std::string& fragment_shader_source);

	void UseProgram();

	unsigned int GetProgramID()
	{
		return ID;
	}

	void setBool(const std::string &name, bool value);
	void setInt(const std::string &name, int value);
	void setFloat(const std::string &name, float value);


private:
	unsigned int ID;
};






#endif