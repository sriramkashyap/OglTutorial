#ifndef GLSHADER_H
#define GLSHADER_H

#include <string>
#include <vector>
#include "GLIncludes.h"

class GLShader
{
protected:
	GLuint shader_handle;
	std::string shader_file;

	GLuint LoadShader(const std::string fname, int type);
public:
	GLShader(const std::string &fname, int type);
	GLuint GetHandle() const;
};

class GLProgram
{
protected:
	GLuint program_handle;
	std::vector<GLShader> shader_list;

	GLuint Compile(const std::vector<GLShader> &shaders);
	GLint GetUniformLocation(const std::string &name) const;
public:

	GLProgram(std::vector<GLShader> &shaders);
	GLuint GetHandle() const;
	
	void  SetUniform(const std::string &name, float value) const;
	void  SetUniform(const std::string &name, int value) const;
};

#endif