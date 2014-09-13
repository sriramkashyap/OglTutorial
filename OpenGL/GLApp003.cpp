#include <iostream>

#include "GLUtils.h"
#include "GLShader.h"
#include "GLTransforms.h"
#include "GLVertexBuffer.h"
#include "GLGeometry.h"
#include "GLApps.h"

GLApp003::GLApp003()
{
	InitScene();
	animating = true;
	rotating = false;
	displacement = 0.0f;
}

void GLApp003::InitScene()
{
	vs = std::make_shared<GLShader>("wave.vs", GL_VERTEX_SHADER);
	ps = std::make_shared<GLShader>("basic.ps", GL_FRAGMENT_SHADER);
	prog = std::make_shared<GLProgram>(std::vector<GLShader>({ *vs, *ps }));
	camera = std::make_shared<GLCamera>();

	auto mesh = GLGeometry::GenMesh(64);
	num_vertices = mesh.size() / 3;

	auto color = GLGeometry::GenColor(num_vertices);

	vbuffer = std::make_shared<GLVertexBuffer>(num_vertices);

	vbuffer->AddElement(&mesh[0], 3);
	vbuffer->AddElement(&color[0], 3);
	vbuffer->GenBuffers();

	glUseProgram(prog->GetHandle());
	glBindVertexArray(vbuffer->GetHandle());

	camera->SetupView(glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	camera->PlaceAt(glm::vec3(glm::sin(time)*4.0f, glm::cos(time)*4.0f, 1.0f));
	prog->SetUniform("transform", camera->GetTransform());

}

void GLApp003::RenderScene(double elapsedMilliseconds)
{
	camera->PlaceAt(glm::vec3(glm::sin(time)*4.0f, glm::cos(time)*4.0f, 1.0f));
	if (rotating)
	{
		prog->SetUniform("transform", camera->GetTransform());
	}
	if (animating)
	{
		prog->SetUniform("phase", time);
	}
	prog->SetUniform("displacement", displacement);

	time += 0.001f * (float)elapsedMilliseconds;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, num_vertices);
	glutSwapBuffers();
	glutPostRedisplay();
}

void GLApp003::HandleInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		running = false;
		break;
	case '1':
		rotating = !rotating;
		break;
	case '2':
		animating = !animating;
		break;
	case '+':
		displacement += 0.01f;
		break;
	case '-':
		displacement -= 0.01f;
		break;
	case 'Z':
		GLMain::EnableDepthTest(true);
		break;
	case 'z':
		GLMain::EnableDepthTest(false);
		break;
	}
}