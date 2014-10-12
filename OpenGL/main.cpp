#include <iostream>
#include "GLMain.h"
#include "GLApps.h"

int main(int argc, char **argv)
{
	GLMain::InitializeGLUT();

	GLMain::Run(GLApp001());
	GLMain::Run(GLApp002());
	GLMain::Run(GLApp003());
	GLMain::Run(GLApp004());

	std::cout << "OpenGL Test Completed" << std::endl;
	return 0;
}

