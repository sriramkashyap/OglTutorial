#ifndef GLAPP_EARTHDEMO_H
#define GLAPP_EARTHDEMO_H

#include "GLApps.h"

class GLApp_EarthDemo : public SimpleGLApp
{
protected:
	std::shared_ptr<GLShader> vs_sky;
	std::shared_ptr<GLShader> ps_sky;
	std::shared_ptr<GLProgram> prog_sky;
	
	std::shared_ptr<GLTransform> sky_scale;
	std::shared_ptr<GLTransform> sun_billboard;

	std::shared_ptr<GLVertexBuffer> vbuffer_sky;
	std::shared_ptr<GLVertexBuffer> vbuffer_sun;

	std::shared_ptr<GLTexture> earth, clouds, lights, sky, sun;
	std::shared_ptr<GLCamera> camera;

	GLGeometry::GLModel sphere, cylinder, plane;

	glm::vec2 cloud_offset;
	glm::vec3 light_pos, eye_pos;
	glm::vec4 light_col, mat_ambient;
	float mat_diffuse, mat_specular;

	bool eye_rotate, light_rotate, cloud_rotate;

public:
	GLApp_EarthDemo();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void HandleInput(unsigned char key, int x, int y);
	void ResizeFunction(int width, int height);
};

#endif
