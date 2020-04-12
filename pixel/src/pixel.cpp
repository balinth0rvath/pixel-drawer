#include "src/pixel_surface.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <unistd.h>
#include  <sys/time.h>
 
#include  <X11/Xlib.h>
#include  <X11/Xatom.h>
#include  <X11/Xutil.h>
 
#include  <GLES2/gl2.h>
#include  <EGL/egl.h>

int  main()
{
	PixelSurface s;
	s.initEGL();
	glViewport ( 0 , 0 , 100 , 100 );
	glClearColor ( 0.0f , 1.0f , 0.07f , 1.0f);    // background color
	glClear ( GL_COLOR_BUFFER_BIT );
	eglSwapBuffers ( s.getEGLDisplay(), s.getEGLSurface() );  // get the rendered buffer to the screen
	sleep(1); 
	s.closeEGL();

	return 0;
}	
