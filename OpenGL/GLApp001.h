#ifndef GLAPP001_H
#define GLAPP001_H

#include <memory>
#include "GLMain.h"

class GLShader;
class GLProgram;
class GLVertexBuffer;

class GLApp001 : public GLApplication
{
protected:
	std::shared_ptr<GLShader> vs;
	std::shared_ptr<GLShader> ps;
	std::shared_ptr<GLProgram> prog;
	std::shared_ptr<GLVertexBuffer> vbuffer;
	float time;
public:
	bool running;

	GLApp001();
	void InitScene();
	void RenderScene();
	bool Running() const;
	void HandleInput(unsigned char key, int x, int y);
};

#endif