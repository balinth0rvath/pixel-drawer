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

struct display { 
	Display    *x_display;
	Window      x_window;
};

struct egl {
	EGLDisplay  eglDisplay;
	EGLConfig*  configs;
	EGLContext  eglContext;
	EGLSurface  eglSurface;
	EGLint major, minor;
};
 
EGLint configList[] = {       // some attributes to set up our egl-interface
	EGL_RED_SIZE, 8,
	EGL_GREEN_SIZE, 8,
	EGL_BLUE_SIZE, 8,
	EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
	EGL_NONE
   };

void initDisplayClient(struct display* display)
{
    display->x_display = XOpenDisplay ( NULL ); 
    if ( display->x_display == NULL ) {
		printf("cannot connect to X server \n");
		exit(1);
    }
 
    Window root  =  DefaultRootWindow( display->x_display );
 
    XSetWindowAttributes  swa;
    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;
 
    display->x_window  =  XCreateWindow (   // create a window with the provided parameters
		display->x_display, 
		root,
		50, 50, 
		200, 200,   
		0,
		CopyFromParent, 
		InputOutput,
		CopyFromParent, 
		CWEventMask,
		&swa );
 
   XMapWindow ( display->x_display , display->x_window );             // make the window visible on the screen
   XStoreName ( display->x_display , display->x_window , "example" ); // give the window a name

}

void initEGL(struct display* display, struct egl* egl)
{
    egl->eglDisplay  =  eglGetDisplay( (EGLNativeDisplayType) display->x_display );
    if ( egl->eglDisplay == EGL_NO_DISPLAY ) 
	{
		  printf("Got no EGL display.");
		  exit(1);
    }
 
    if ( !eglInitialize( egl->eglDisplay, &egl->major, &egl->minor ) ) {
		  printf("Unable to initialize EGL");
		  exit(1);
   	}
 
	printf("EGL major %i, minor %i\n",egl->major, egl->minor);

    EGLint maxConfigs, numConfigs;
	numConfigs = 0;

	if (eglGetConfigs(egl->eglDisplay, NULL, 0, &maxConfigs)!=EGL_TRUE)
	{
		printf("Error determining egl configs\n");
		exit(1);
	}

	printf("Max configs: %i\n", maxConfigs);
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

}

void closeEGL(struct egl* egl)
{
   eglDestroyContext ( egl->eglDisplay, egl->eglContext );
   eglDestroySurface ( egl->eglDisplay, egl->eglSurface );
   eglTerminate      ( egl->eglDisplay );
}

void closeDisplayClient(struct display* display)
{
   XDestroyWindow    ( display->x_display, display->x_window );
   XCloseDisplay     ( display->x_display );
}

void render(struct egl* egl)
{
	glViewport ( 0 , 0 , 100 , 100 );
	glClearColor ( 0.0f , 1.0f , 0.07f , 1.0f);    // background color
	glClear ( GL_COLOR_BUFFER_BIT );
	eglSwapBuffers ( egl->eglDisplay, egl->eglSurface );  // get the rendered buffer to the screen
}

int  main()
{
	struct display display = { 0 }; 
	struct egl egl = { 0 };

	initDisplayClient(&display);
	initEGL(&display, &egl);

	render(&egl);

	sleep(1); 

	closeEGL(&egl);
	closeDisplayClient(&display);

	return 0;
}	
