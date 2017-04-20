#include <iostream>
#include "GLMain.h"
#include "GLApps.h"
#include "GLAppEarth.h"

int main(int argc, char **argv)
{
	GLMain::InitializeGLUT();

	GLMain::Run(GLApp_FirstTriangle());	//Single triangle (Basics)
	GLMain::Run(GLApp_CameraBasics());	//Rotating square (Camera)
	GLMain::Run(GLApp_WavyMesh());		//Wavy Mesh (Vertex Animation)
	GLMain::Run(GLApp_CreateTexture());	//Random texture (Textures)
	GLMain::Run(GLApp_WoodTexture());	//Wood texture (FreeImage)
	GLMain::Run(GLApp_Blending());		//Blending and drawing multiple objects
	GLMain::Run(GLApp_Cueball());		//Cueball lighting demo
	GLMain::Run(GLApp_EarthDemo());		//Earth Demo
		
	std::cout << "OpenGL Test Completed" << std::endl;
	return 0;
}

