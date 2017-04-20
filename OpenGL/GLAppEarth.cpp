#include <iostream>

#include "GLUtils.h"
#include "GLShader.h"
#include "GLTransforms.h"
#include "GLVertexBuffer.h"
#include "GLTexture.h"
#include "GLGeometry.h"
#include "GLAppEarth.h"

using namespace GLGeometry;

GLApp_EarthDemo::GLApp_EarthDemo() :
light_pos(5.0f, 5.0f, 0.0f),
light_col(1.0f, 1.0f, 0.6f, 1.0f),
mat_ambient(0.01f, 0.01f, 0.01f, 0.0f),
mat_diffuse(1.0f),
mat_specular(32.0f),
cloud_offset(0.0f, 0.0f),
eye_rotate(true),
light_rotate(true),
cloud_rotate(true)
{
	InitScene();
}

void GLApp_EarthDemo::InitScene()
{
	vs = std::make_shared<GLShader>("earth.vs", GL_VERTEX_SHADER);
	ps = std::make_shared<GLShader>("earth.ps", GL_FRAGMENT_SHADER);
	prog = std::make_shared<GLProgram>(std::vector<GLShader>({ *vs, *ps }));
	camera = std::make_shared<GLCamera>();

	vs_sky = std::make_shared<GLShader>("texture.vs", GL_VERTEX_SHADER);
	ps_sky = std::make_shared<GLShader>("texture.ps", GL_FRAGMENT_SHADER);
	prog_sky = std::make_shared<GLProgram>(std::vector<GLShader>({ *vs_sky, *ps_sky }));

	sphere		= GLGeometry::GenSphere(32, 32);
	cylinder	= GLGeometry::GenCylinder(1, 16);
	plane		= GLGeometry::GenBillBoard();

	vbuffer = std::make_shared<GLVertexBuffer>(sphere.numVertices());
	vbuffer_sky = std::make_shared<GLVertexBuffer>(cylinder.numVertices());
	vbuffer_sun = std::make_shared<GLVertexBuffer>(plane.numVertices());

	earth = std::make_shared<GLTexture>();
	clouds = std::make_shared<GLTexture>();
	lights = std::make_shared<GLTexture>();
	sky = std::make_shared<GLTexture>();
	sun = std::make_shared<GLTexture>();

	vbuffer->AddElement(&sphere.position[0], 3);
	vbuffer->AddElement(&sphere.normal[0], 3);
	vbuffer->AddElement(&sphere.color[0], 3);
	vbuffer->AddElement(&sphere.texcoord[0], 2);
	vbuffer->GenBuffers();

	vbuffer_sky->AddElement(&cylinder.position[0], 3);
	vbuffer_sky->AddElement(&cylinder.texcoord[0], 2);
	vbuffer_sky->GenBuffers();

	vbuffer_sun->AddElement(&plane.position[0], 3);
	vbuffer_sun->AddElement(&plane.texcoord[0], 2);
	vbuffer_sun->GenBuffers();

	sky_scale = std::make_shared<GLTransform>();
	sky_scale->Scale(glm::vec3(16.0, 16.0, 16.0));

	sun_billboard = std::make_shared<GLTransform>();

	camera->SetupView(glm::vec3(0.0f, 8.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

	earth->GetTextureFromFile("earth.jpg", GL_BGR);
	clouds->GetTextureFromFile("earth_clouds.jpg", GL_BGR);
	lights->GetTextureFromFile("earth_lights.jpg", GL_BGR);
	sky->GetTextureFromFile("nightsky.jpg", GL_BGR);
	sun->GetTextureFromFile("sun.png", GL_BGRA);

	earth->LoadTextureToGPU();
	clouds->LoadTextureToGPU();
	lights->LoadTextureToGPU();
	sky->LoadTextureToGPU();
	sun->LoadTextureToGPU();

	GLMain::EnableDepthTest(true);
}

void GLApp_EarthDemo::RenderScene(double elapsedMilliseconds)
{
	//Overall settings
	if (eye_rotate) eye_pos = glm::vec3(glm::sin(time / 4.0)*8.0f, glm::cos(time / 4.0)*8.0f, 2.0f);
	if (light_rotate) light_pos = glm::vec3(glm::sin(time)*5.0f, glm::cos(time)*5.0f, 0.0f);
	if (cloud_rotate) cloud_offset = glm::vec2(-time / 100.0f, 0.0f);
	
	camera->PlaceAt(eye_pos);

	//Draw Sphere
	glUseProgram(prog->GetHandle());
	glBindVertexArray(vbuffer->GetHandle());
	
	prog->SetUniform("transform", camera->GetTransform());
	
	prog->SetUniform("light_pos", light_pos);
	prog->SetUniform("eye_pos", eye_pos);
	prog->SetUniform("light_col", light_col);
	prog->SetUniform("mat_ambient", mat_ambient);
	prog->SetUniform("mat_diffuse", mat_diffuse);
	prog->SetUniform("mat_specular", mat_specular);
	prog->SetUniform("cloud_offset", cloud_offset);
	
	earth->Use(prog->GetUniformLocation("earth"), 0);
	clouds->Use(prog->GetUniformLocation("clouds"), 1);
	lights->Use(prog->GetUniformLocation("night"), 2);
	
	time += 0.001f * (float)elapsedMilliseconds;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, sphere.numVertices());

	//Draw background
	glUseProgram(prog_sky->GetHandle());
	glBindVertexArray(vbuffer_sky->GetHandle());

	prog_sky->SetUniform("transform", camera->GetTransform() * sky_scale->GetTransform());
	prog_sky->SetUniform("texScale", glm::vec2(4.0f,4.0f));
	prog_sky->SetUniform("brightness", 0.5f);
	sky->Use(prog_sky->GetUniformLocation("tex"), 0);
	glDrawArrays(GL_TRIANGLES, 0, cylinder.numVertices());

	//Draw Sun
	glBindVertexArray(vbuffer_sun->GetHandle());

	sun_billboard->Translate(light_pos);
	sun_billboard->Billboard(eye_pos - light_pos, glm::vec3(0.0, 0.0, -1.0));
	prog_sky->SetUniform("transform", camera->GetTransform() * sun_billboard->GetTransform());
	prog_sky->SetUniform("texScale", glm::vec2(1.0f, 1.0f));
	prog_sky->SetUniform("brightness", 1.0f);
	sun->Use(prog_sky->GetUniformLocation("tex"), 0);
	GLMain::EnableBlend(true);
	glDrawArrays(GL_TRIANGLES, 0, plane.numVertices());

	GLMain::EnableBlend(false);
	glutSwapBuffers();
	glutPostRedisplay();
}

void GLApp_EarthDemo::HandleInput(unsigned char key, int x, int y)
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
	case '4':
		eye_rotate = !eye_rotate;
		break;
	case '5':
		light_rotate = !light_rotate;
		break;
	case '6':
		cloud_rotate = !cloud_rotate;
		break;
	}
}

void GLApp_EarthDemo::ResizeFunction(int width, int height)
{
	glViewport(0, 0, width, height);
	camera->SetupProjection(75.0f, static_cast<float>(width) / height, 0.001f, 1000.0f);
}