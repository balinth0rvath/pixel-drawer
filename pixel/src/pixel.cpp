#include "src/pixel_surface.h"
#include "src/pixel_gl_program_manager.h"
#include "src/pixel_renderer.h"
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
#include <iostream>

int  main()
{
	auto pixelGLProgramManager = std::make_unique<PixelGLProgramManager>();
	auto pixelSurface = std::make_unique<PixelSurface>();
	auto pixelRenderer = std::make_unique<PixelRenderer>();
	pixelSurface->initEGL();
	pixelGLProgramManager->init();

	if (!pixelGLProgramManager->getProgramObject())
		return 1;

	pixelRenderer->render(pixelGLProgramManager, pixelSurface);
	
	sleep(5); 
	pixelSurface->closeEGL();

	return 0;
}	
