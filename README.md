OglTutorial
===========

Getting Started:
----------------
> Download and install Visual Studio 2015 Community Edition
  Link : https://www.microsoft.com/en-in/download/details.aspx?id=48146
  
> Download freeglut binary release for MSVC and unzip it to "C:\opengl\freeglut"
  Link : http://www.transmissionzero.co.uk/software/freeglut-devel/ 

  You should now have the following directories:
	C:\opengl\freeglut\bin
	C:\opengl\freeglut\include
	C:\opengl\freeglut\lib
 
> Download GLEW Windows binary release and unzip it to "C:\opengl\glew"
  Link : http://glew.sourceforge.net/
  
  You should now have the following directories:
	C:\opengl\glew\bin
	C:\opengl\glew\include
	C:\opengl\glew\lib

> Download GLM headers and unzip to "C:\opengl\glm"
  Link : http://sourceforge.net/projects/ogl-math/files/

  You should now have the following directories:	
	C:\opengl\glm\glm\gtc
	C:\opengl\glm\glm\gtx
	C:\opengl\glm\glm\detail

> Download FreeImage binary distribution and unzip to "C:\opengl\FreeImage"	
  Link : http://freeimage.sourceforge.net/download.html
  
  You should now have the following files:
    C:\opengl\FreeImage\Dist\FreeImage.lib
    C:\opengl\FreeImage\Dist\FreeImage.h

Build and Run:
--------------
	Now, open 'OpenGL.sln' in Visual Studio, build and run the application. 
	You should see the first sample application(a triangle). 
	Press escape to launch the next sample, and the next...
	Controls can be accessed through number keys

Using a different compiler (g++/Visual Studio 2011...):
-------------------------------------------------------
> Create a new project / makefile and include all the cpp/header files

> Add this to the compiler include path (modify paths as necessary):
	C:\opengl\glew\include;C:\opengl\freeglut\include;C:\opengl\glm;C:\opengl\FreeImage\Dist
	
> Add this to the library path (modify paths as necessary):
	C:\opengl\glew\lib\Release\Win32;C:\opengl\freeglut\lib;C:\opengl\FreeImage\Dist
	
> Add this to the library list:
	freeglut.lib;glew32.lib;FreeImage.lib
