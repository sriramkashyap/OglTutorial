#include <iostream>

#include "GLUtils.h"
#include "GLShader.h"
#include "GLVertexBuffer.h"
#include "GLApp001.h"

GLApp001::GLApp001()
{
	InitScene();
	running = true;
}

void GLApp001::InitScene()
{
	vs		= std::make_shared<GLShader>("basic.vs", GL_VERTEX_SHADER);
	ps		= std::make_shared<GLShader>("basic.ps", GL_FRAGMENT_SHADER);
	prog	= std::make_shared<GLProgram>(std::vector<GLShader>({ *vs, *ps }));
	vbuffer = std::make_shared<GLVertexBuffer>(4);

	time = 0.0f;

	float positionData[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		
		0.0f,-1.0f, 0.0f,
		-1.0f,0.0f, 0.0f
	};

	float colorData[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f		
	};

	vbuffer->AddElement(positionData, 3);
	vbuffer->AddElement(colorData, 3);
	vbuffer->GenBuffers();

	glUseProgram(prog->GetHandle());
	glBindVertexArray(vbuffer->GetHandle());
}

bool GLApp001::Running() const
{
	return running;
}

void GLApp001::RenderScene()
{
	prog->SetUniform("rotation", time);
	time += 0.0001f;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glutSwapBuffers();
	glutPostRedisplay();
}

void GLApp001::HandleInput(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		running = false;
	}
}