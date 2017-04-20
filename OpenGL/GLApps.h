#ifndef GLAPPS_H
#define GLAPPS_H

#include <memory>
#include "GLMain.h"
#include <glm/glm.hpp>
#include "GLGeometry.h"

class GLShader;
class GLProgram;
class GLVertexBuffer;
class GLTexture;
class GLCamera;
class GLTransform;

class SimpleGLApp : public GLApplication
{
protected:
	std::shared_ptr<GLShader> vs;
	std::shared_ptr<GLShader> ps;
	std::shared_ptr<GLProgram> prog;
	std::shared_ptr<GLVertexBuffer> vbuffer;
	float time;
	bool running;
public:
	SimpleGLApp();
	bool Running() const;
	virtual void HandleInput(unsigned char key, int x, int y);
	virtual void ResizeFunction(int width, int height);
};

class GLApp_FirstTriangle : public SimpleGLApp
{
public:
	GLApp_FirstTriangle();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
};

class GLApp_CameraBasics : public SimpleGLApp
{
protected:
	std::shared_ptr<GLCamera> camera;
public:
	GLApp_CameraBasics();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void ResizeFunction(int width, int height);
};

class GLApp_WavyMesh : public SimpleGLApp
{
protected:
	int num_vertices;
	bool animating, rotating;
	float displacement;
	std::shared_ptr<GLCamera> camera;
public:
	GLApp_WavyMesh();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void HandleInput(unsigned char key, int x, int y);
	void ResizeFunction(int width, int height);
};

class GLApp_CreateTexture : public SimpleGLApp
{
protected:
	std::shared_ptr<GLTexture> texture;
	std::shared_ptr<GLCamera> camera;
public:
	GLApp_CreateTexture();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void ResizeFunction(int width, int height);
};

class GLApp_WoodTexture : public SimpleGLApp
{
protected:
	std::shared_ptr<GLTexture> texture;
	std::shared_ptr<GLCamera> camera;
	glm::vec2 tex_scale, tex_offset;
public:
	GLApp_WoodTexture();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void HandleInput(unsigned char key, int x, int y);
	void ResizeFunction(int width, int height);
};

class GLApp_Blending : public SimpleGLApp
{
protected:
	int numVertices;
	std::shared_ptr<GLCamera> camera;
	std::shared_ptr<GLTexture> texture;

	std::shared_ptr<GLShader> vs2;
	std::shared_ptr<GLShader> ps2;
	std::shared_ptr<GLProgram> prog2;
	std::shared_ptr<GLVertexBuffer> vbuffer2;

	bool enable_blend;

public:
	GLApp_Blending();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void HandleInput(unsigned char key, int x, int y);
	void ResizeFunction(int width, int height);
};

class GLApp_Cueball : public SimpleGLApp
{
protected:
	std::shared_ptr<GLCamera> camera;
	std::shared_ptr<GLTexture> texture;

	GLGeometry::GLModel sphere;

	glm::vec3 light_pos;
	glm::vec4 light_col, mat_ambient;
	float mat_diffuse, mat_specular;

public:
	GLApp_Cueball();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void HandleInput(unsigned char key, int x, int y);
	void ResizeFunction(int width, int height);
};

#endif