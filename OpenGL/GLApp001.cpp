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
	GLShader vs = GLShader("basic.vs", GL_VERTEX_SHADER);
	GLShader ps = GLShader("basic.ps", GL_FRAGMENT_SHADER);
	GLProgram prog = GLProgram(std::vector<GLShader>({ vs, ps }));

	GLVertexBuffer vb(3);

	float positionData[] = {
		-0.8f, -0.8f, 0.0f,
		0.8f, 0.0f, 0.0f,
		0.0f, 0.8f, 0.0f };

	float colorData[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f };

	vb.AddElement(positionData, 3);
	vb.AddElement(colorData, 3);
	vb.GenBuffers();

	glUseProgram(prog.GetHandle());
	glBindVertexArray(vb.GetHandle());
}

bool GLApp001::Running() const
{
	return running;
}

void GLApp001::RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
}

void GLApp001::HandleInput(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		running = false;
	}
}