#ifndef GLAPPS_H
#define GLAPPS_H

#include <memory>
#include "GLMain.h"

class GLShader;
class GLProgram;
class GLVertexBuffer;
class GLTexture;
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
	SimpleGLApp();
	bool Running() const;
	virtual void HandleInput(unsigned char key, int x, int y);
	virtual void ResizeFunction(int width, int height);
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
	void ResizeFunction(int width, int height);
};

class GLApp003 : public SimpleGLApp
{
protected:
	int num_vertices;
	bool animating, rotating;
	float displacement;
	std::shared_ptr<GLCamera> camera;
public:
	GLApp003();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void HandleInput(unsigned char key, int x, int y);
	void ResizeFunction(int width, int height);
};

class GLApp004 : public SimpleGLApp
{
protected:
	std::shared_ptr<GLTexture> texture;
	std::shared_ptr<GLCamera> camera;
public:
	GLApp004();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void ResizeFunction(int width, int height);
};

class GLApp005 : public SimpleGLApp
{
protected:
	std::shared_ptr<GLTexture> texture;
	std::shared_ptr<GLCamera> camera;
public:
	GLApp005();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void ResizeFunction(int width, int height);
};

class GLApp006 : public SimpleGLApp
{
protected:
	std::shared_ptr<GLTexture> texture;
	std::shared_ptr<GLCamera> camera;
	int num_vertices;
public:
	GLApp006();
	void InitScene();
	void RenderScene(double elapsedMilliseconds);
	void ResizeFunction(int width, int height);
};


#endif