#include <iostream>
#include "GLMain.h"
#include "GLApps.h"

int main(int argc, char **argv)
{
	GLMain::InitializeGLUT();

	GLMain::Run(GLApp001());	//Single triangle (Basics)
	GLMain::Run(GLApp002());	//Rotating square (Camera)
	GLMain::Run(GLApp003());	//Wavy Mesh (Vertex Animation)
	GLMain::Run(GLApp004());	//Random texture (Textures)
	GLMain::Run(GLApp005());	//Wood texture (FreeImage)

	std::cout << "OpenGL Test Completed" << std::endl;
	return 0;
}

