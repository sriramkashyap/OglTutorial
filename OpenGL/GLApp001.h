#ifndef GLAPP001_H
#define GLAPP001_H

#include "GLMain.h"

class GLApp001 : public GLApplication
{
public:
	bool running;

	GLApp001();
	void InitScene();
	void RenderScene();
	bool Running() const;
	void HandleInput(unsigned char key, int x, int y);
};

#endif