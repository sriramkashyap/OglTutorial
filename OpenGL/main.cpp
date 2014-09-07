#include <iostream>
#include "GLMain.h"
#include "GLApp001.h"

class NewOne : public GLMain
{

};

int main(int argc, char **argv)
{
	GLMain::InitializeGLUT();

	GLMain::Run(GLApp001());
	
	std::cout << "OpenGL Test Completed" << std::endl;
	return 0;
}

