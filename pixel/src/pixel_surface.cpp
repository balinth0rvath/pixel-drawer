#include "pixel_surface.h"

PixelSurface::PixelSurface() {
	this->configList = { 
	EGL_RED_SIZE, 8,
	EGL_GREEN_SIZE, 8,
	EGL_BLUE_SIZE, 8,
	EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
	EGL_NONE};
}

PixelSurface::~PixelSurface() {};

void PixelSurface::initEGL() {
    this->eglDisplay  =  eglGetDisplay( (EGLNativeDisplayType) this->xDisplay );
    if ( this->eglDisplay == EGL_NO_DISPLAY ) 
	{
		  std::cout << "Got no EGL display." << std::endl;
		  exit(1);
    }
 
    if ( !eglInitialize( this->eglDisplay, &this->major, &this->minor ) ) {
		  std::cout << "Unable to initialize EGL" << std::endl;
		  exit(1);
   	}
 
	std::cout << "EGL major" << this->major << ", minor " << this->minor << std::endl;

    EGLint maxConfigs, numConfigs;
	numConfigs = 0;

	if (eglGetConfigs(this->eglDisplay, NULL, 0, &maxConfigs)!=EGL_TRUE)
	{
		std::cout << "Error determining egl configs" << std::endl;
		exit(1);
	}
/*
	std::cout << "Max configs: " << maxConfigs << std::endl;
	egl->configs = (EGLConfig*)calloc((int)maxConfigs,sizeof(EGLConfig));
    if ( !eglChooseConfig( egl->eglDisplay, configList, egl->configs, maxConfigs, &numConfigs ) ) {
		GLenum e = glGetError();
		printf("Error choosing egl configs: %i num configs: %i \n", e, numConfigs); 
		exit(1);
    }
 
    egl->eglSurface = eglCreateWindowSurface ( egl->eglDisplay, *egl->configs, display->x_window, NULL );
    if ( egl->eglSurface == EGL_NO_SURFACE ) {
      printf("Unable to create EGL surface eglError: %i \n",eglGetError());
      exit(1);
   }
 
   //// egl-contexts collect all state descriptions needed required for operation
   EGLint ctxattr[] = {
      EGL_CONTEXT_CLIENT_VERSION, 2,
      EGL_NONE
   };
   egl->eglContext = eglCreateContext ( egl->eglDisplay, *egl->configs, EGL_NO_CONTEXT, ctxattr );
   if ( egl->eglContext == EGL_NO_CONTEXT ) {
      printf("Unable to create EGL context eglError: %i \n" , eglGetError());
      exit(1);
   }
 
   //// associate the egl-context with the egl-surface
   eglMakeCurrent( egl->eglDisplay, egl->eglSurface, egl->eglSurface, egl->eglContext );
*/

};
void PixelSurface::initDisplayClient() {
    this->xDisplay = XOpenDisplay ( NULL ); 

    if ( this->xDisplay == NULL ) {
		std::cout << "cannot connect to X server " << std::endl;
		exit(1);
    }
 
    Window root  =  DefaultRootWindow( this->xDisplay );
 
    XSetWindowAttributes  swa;
    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;
 
    this->xWindow  = XCreateWindow (   // create a window with the provided parameters
		this->xDisplay, 
		root,
		50, 50, 
		200, 200,   
		0,
		CopyFromParent, 
		InputOutput,
		CopyFromParent, 
		CWEventMask,
		&swa );
 
   XMapWindow ( this->xDisplay , this->xWindow );             // make the window visible on the screen

   XStoreName ( this->xDisplay , this->xWindow , "example" ); // give the window a name

};
