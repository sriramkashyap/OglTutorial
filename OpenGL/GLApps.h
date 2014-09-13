#ifndef GLAPPS_H
#define GLAPPS_H

#include <memory>
#include "GLMain.h"

class GLShader;
class GLProgram;
class GLVertexBuffer;
class GLCamera;

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
	SimpleGLApp()
	{
		running = true;
		time = 0.0f;
	}

	bool Running() const
	{
		return running;
	}

	virtual void HandleInput(unsigned char key, int x, int y)
	{
		if (key == 27)
		{
			running = false;
		}
	}
};

class GLApp001 : public SimpleGLApp
{
public:
	GLApp001();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
};

class GLApp002 : public SimpleGLApp
{
protected:
	std::shared_ptr<GLCamera> camera;
public:
	GLApp002();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
};

class GLApp003 : public SimpleGLApp
{
protected:
	std::shared_ptr<GLCamera> camera;
	int num_vertices;
	bool animating, rotating;
	float displacement;
public:
	GLApp003();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void HandleInput(unsigned char key, int x, int y);
};
#endif