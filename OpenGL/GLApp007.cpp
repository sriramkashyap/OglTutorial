#include <iostream>

#include "GLUtils.h"
#include "GLShader.h"
#include "GLTransforms.h"
#include "GLVertexBuffer.h"
#include "GLTexture.h"
#include "GLApps.h"
#include "GLGeometry.h"

using namespace GLGeometry;

GLApp007::GLApp007() :
light_pos(5.0f, 5.0f, 0.0f),
light_col(1.0f, 1.0f, 0.6f, 1.0f),
mat_ambient(0.1f, 0.1f, 0.1f, 0.0f),
mat_diffuse(0.0f),
mat_specular(0.0f)
{
	InitScene();
}

void GLApp007::InitScene()
{
	vs = std::make_shared<GLShader>("lighting.vs", GL_VERTEX_SHADER);
	ps = std::make_shared<GLShader>("lighting.ps", GL_FRAGMENT_SHADER);
	prog = std::make_shared<GLProgram>(std::vector<GLShader>({ *vs, *ps }));
	camera = std::make_shared<GLCamera>();
	texture = std::make_shared<GLTexture>();

	sphere = GLGeometry::GenSphere(48, 48);

	vbuffer = std::make_shared<GLVertexBuffer>(sphere.numVertices());

	vbuffer->AddElement(&sphere.position[0], 3);
	vbuffer->AddElement(&sphere.normal[0], 3);
	vbuffer->AddElement(&sphere.color[0], 3);
	vbuffer->AddElement(&sphere.texcoord[0], 2);
	vbuffer->GenBuffers();

	texture->GetTextureFromFile("cueball.jpg", GL_BGR);
	texture->LoadTextureToGPU();

	glUseProgram(prog->GetHandle());
	glBindVertexArray(vbuffer->GetHandle());

	camera->SetupView(glm::vec3(0.0f, 8.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

	GLMain::EnableDepthTest(true);
	GLMain::EnableBlend(false);
}

void GLApp007::RenderScene(double elapsedMilliseconds)
{
	//Overall settings
	glm::vec3 eye_pos = glm::vec3(glm::sin(time / 2.0)*8.0f, glm::cos(time / 2.0)*8.0f, 0.0f);
	light_pos = glm::vec3(glm::sin(time)*5.0f, glm::cos(time)*5.0f, 0.0f);
	camera->PlaceAt(eye_pos);

	//Select Sphere Shaders and Vertex Data
	glUseProgram(prog->GetHandle());
	glBindVertexArray(vbuffer->GetHandle());

	//Set shader parameters
	prog->SetUniform("view_transform", camera->GetTransform());
	prog->SetUniform("light_pos", light_pos);
	prog->SetUniform("eye_pos", eye_pos);
	prog->SetUniform("light_col", light_col);
	prog->SetUniform("mat_ambient", mat_ambient);
	prog->SetUniform("mat_diffuse", mat_diffuse);
	prog->SetUniform("mat_specular", mat_specular);
	texture->Use(prog->GetUniformLocation("tex"));

	//Clear existing buffer and draw sphere
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, sphere.numVertices());

	//Display result on screen
	glutSwapBuffers();
	glutPostRedisplay();

	//Increment elapsed time
	time += 0.001f * (float)elapsedMilliseconds;
}

void GLApp007::HandleInput(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		running = false;
		break;
	case '1':
		mat_ambient += glm::vec4(0.05, 0.05, 0.05, 0.0);
		break;
	case '!':
		mat_ambient -= glm::vec4(0.05, 0.05, 0.05, 0.0);
		break;
	case '2':
		mat_diffuse += 0.1f;
		break;
	case '@':
		mat_diffuse -= 0.1f;
		break;
	case '3':
		mat_specular += 1.0f;
		break;
	case '#':
		mat_specular -= 1.0f;
		break;

	}
}

void GLApp007::ResizeFunction(int width, int height)
{
	glViewport(0, 0, width, height);
	camera->SetupProjection(75.0f, static_cast<float>(width) / height, 0.001f, 1000.0f);
}