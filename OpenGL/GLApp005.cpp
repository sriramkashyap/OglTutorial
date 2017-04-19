#include <iostream>

#include "GLUtils.h"
#include "GLShader.h"
#include "GLTransforms.h"
#include "GLVertexBuffer.h"
#include "GLTexture.h"
#include "GLApps.h"

GLApp_WoodTexture::GLApp_WoodTexture() : 
	tex_scale(1.0f,1.0f), 
	tex_offset(0.0f,0.0f)
{
	InitScene();
}

void GLApp_WoodTexture::InitScene()
{
	vs		= std::make_shared<GLShader>("texture.vs", GL_VERTEX_SHADER);
	ps		= std::make_shared<GLShader>("texture.ps", GL_FRAGMENT_SHADER);
	prog	= std::make_shared<GLProgram>(*vs, *ps);
	vbuffer = std::make_shared<GLVertexBuffer>(4);
	texture = std::make_shared<GLTexture>();

	camera = std::make_shared<GLCamera>();

	float positionData[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		-1.0f, 0.0f, 0.0f
	};

	float texData[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f
	};

	vbuffer->AddElement(positionData, 3);
	vbuffer->AddElement(texData, 2);
	vbuffer->GenBuffers();

	glUseProgram(prog->GetHandle());
	glBindVertexArray(vbuffer->GetHandle());

	camera->SetupView(glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	//texture->GenerateTexture(16,16,GL_TEXGEN_CHECKER);
	texture->GetTextureFromFile("wood.jpg", GL_BGR);
	texture->LoadTextureToGPU();

	GLMain::EnableDepthTest(false);
}

void GLApp_WoodTexture::RenderScene(double elapsedMilliseconds)
{
	camera->PlaceAt(glm::vec3(glm::sin(time)*4.0f, glm::cos(time)*4.0f, 2.0f));
	
	prog->SetUniform("transform", camera->GetTransform());
	prog->SetUniform("texOffset", tex_offset);
	prog->SetUniform("texScale", tex_scale);

	texture->Use(prog->GetUniformLocation("tex"));
	//time += 0.0001f * (float)elapsedMilliseconds;
	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glutSwapBuffers();
	glutPostRedisplay();
}

void GLApp_WoodTexture::HandleInput(unsigned char key, int x, int y)
{
	const glm::vec2 offset(0.01, 0.01);
	const glm::vec2 scale(0.01, 0.01);

	switch (key)
	{
	case 27:
		running = false;
		break;
	case '1':
		tex_offset += offset;
		break;
	case '!':
		tex_offset -= offset;
		break;
	case '2':
		tex_scale += scale;
		break;
	case '@':
		tex_scale -= scale;
		break;
	}
}

void GLApp_WoodTexture::ResizeFunction(int width, int height)
{
	glViewport(0, 0, width, height);
	camera->SetupProjection(75.0f, static_cast<float>(width) / height, 0.001f, 1000.0f);
}