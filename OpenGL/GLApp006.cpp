#include <iostream>

#include "GLUtils.h"
#include "GLShader.h"
#include "GLTransforms.h"
#include "GLVertexBuffer.h"
#include "GLTexture.h"
#include "GLApps.h"
#include "GLGeometry.h"

GLApp006::GLApp006()
{
	InitScene();
}

void GLApp006::InitScene()
{
	vs = std::make_shared<GLShader>("lighting.vs", GL_VERTEX_SHADER);
	ps = std::make_shared<GLShader>("lighting.ps", GL_FRAGMENT_SHADER);
	prog = std::make_shared<GLProgram>(std::vector<GLShader>({ *vs, *ps }));
	camera = std::make_shared<GLCamera>();

	auto sphere = GLGeometry::GenSphere(8, 8);
	num_vertices = sphere.numVertices();

	vbuffer = std::make_shared<GLVertexBuffer>(num_vertices);
	texture = std::make_shared<GLTexture>();

	vbuffer->AddElement(&sphere.position[0], 3);
	vbuffer->AddElement(&sphere.normal[0], 3);
	vbuffer->AddElement(&sphere.color[0], 3);
	vbuffer->AddElement(&sphere.texcoord[0], 2);
	vbuffer->GenBuffers();

	glUseProgram(prog->GetHandle());
	glBindVertexArray(vbuffer->GetHandle());

	camera->SetupView(glm::vec3(0.0f,1.0f,1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

	texture->GetTextureFromFile("wood.jpg", GL_BGR);
	texture->LoadTextureToGPU();

	GLMain::EnableDepthTest(true);
}

void GLApp006::RenderScene(double elapsedMilliseconds)
{
	camera->PlaceAt(glm::vec3(glm::sin(time)*8.0f, glm::cos(time)*8.0f, 2.0f));
	prog->SetUniform("transform", camera->GetTransform());
	texture->Use(prog->GetUniformLocation("tex"));
	time += 0.001f * (float)elapsedMilliseconds;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, num_vertices);
	glutSwapBuffers();
	glutPostRedisplay();
}

void GLApp006::ResizeFunction(int width, int height)
{
	glViewport(0, 0, width, height);
	camera->SetupProjection(75.0f, static_cast<float>(width) / height, 0.001f, 1000.0f);
}