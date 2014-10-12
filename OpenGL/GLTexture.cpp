#include "GLTexture.h"

GLTexture::GLTexture()
{
	texture_id = GL_INVALID_VALUE;
	raw_data = NULL;
	format = GL_RGBA;
}

void GLTexture::GenerateTexture(GLuint width, GLuint height, GlTextureGenerator type)
{
	this->width = width;
	this->height = height;
	if (raw_data != NULL) { delete[] raw_data; }
	raw_data = new GLuint[width * height];

	switch (type)
	{
	case GL_TEXGEN_CHECKER:
		for (uint32_t i = 0; i < width * height; i++)
		{
			int row = (i / height) % 8;
			int col = (i % width) % 8;
			raw_data[i] = ((row < 4 && col < 4) || (row >= 4 && col >= 4)) ? 0xffffffff : 0x0;
		}
		break;
	case GL_TEXGEN_RANDOM:
		for (uint32_t i = 0; i < width * height; i++)
		{
			float randval = static_cast<float>(rand()) / RAND_MAX;
			raw_data[i] = static_cast<GLuint>(0xFFFFFFFF * randval);
		}		
		break;
	}
}

void GLTexture::LoadTextureToGPU()
{
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_LINEAR or GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); //GL_CLAMP_TO_EDGE or GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE,raw_data);
}

void GLTexture::Use(GLuint uniform_loc, GLuint texture_position)
{
	GLuint uniform_mytexture = 0;
	glActiveTexture(GL_TEXTURE0 + texture_position);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	glUniform1i(uniform_loc, texture_position);
}

GLTexture::~GLTexture()
{
	if (texture_id != GL_INVALID_VALUE)
	{
		glDeleteTextures(1, &texture_id);
	}

	if (raw_data != NULL)
	{
		delete[] raw_data;
	}
}