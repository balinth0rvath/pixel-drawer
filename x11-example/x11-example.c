//  gcc x11-example.c -lX11 -lEGL -lGLESv2
#include <stdio.h>
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
	EGLDisplay  egl_display;
	EGLContext  egl_context;
	EGLSurface  egl_surface;
};
 
EGLint attr[] = {       // some attributes to set up our egl-interface
	EGL_RED_SIZE, 8,
	EGL_GREEN_SIZE, 8,
	EGL_BLUE_SIZE, 8,
	EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	EGL_RENDERABLE_TYPE,
	EGL_OPENGL_ES2_BIT,
	EGL_NONE
   };

int  main()
{
	struct display display = { 0 }; 
	struct egl egl = { 0 };
    display.x_display = XOpenDisplay ( NULL ); 
    if ( display.x_display == NULL ) {
		printf("cannot connect to X server \n");
		return 1;
    }
 
    Window root  =  DefaultRootWindow( display.x_display );
 
    XSetWindowAttributes  swa;
    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;
 
    display.x_window  =  XCreateWindow (   // create a window with the provided parameters
		display.x_display, 
		root,
		50, 50, 
		200, 200,   
		0,
		CopyFromParent, 
		InputOutput,
		CopyFromParent, 
		CWEventMask,
		&swa );
 
    XSetWindowAttributes  xattr;
    Atom  atom;
    int   one = 1;
 
    xattr.override_redirect = False;
    XChangeWindowAttributes ( 
		display.x_display, 
		display.x_window, 
		CWOverrideRedirect, 
		&xattr );

   XMapWindow ( display.x_display , display.x_window );             // make the window visible on the screen
   XStoreName ( display.x_display , display.x_window , "example" ); // give the window a name

   egl.egl_display  =  eglGetDisplay( (EGLNativeDisplayType) display.x_display );
   if ( egl.egl_display == EGL_NO_DISPLAY ) {
      printf("Got no EGL display.");
      return 1;
   }
 
   if ( !eglInitialize( egl.egl_display, NULL, NULL ) ) {
      printf("Unable to initialize EGL");
      return 1;
   }
 
   EGLConfig  ecfg;
   EGLint     num_config;
   if ( !eglChooseConfig( egl.egl_display, attr, &ecfg, 1, &num_config ) ) {
      printf("Failed to choose config eglError: %i \n", eglGetError());
      return 1;
   }
 
   if ( num_config != 1 ) {
      printf("Didn't get exactly one config, but  %i \n", num_config);
      return 1;
   }
 
   egl.egl_surface = eglCreateWindowSurface ( egl.egl_display, ecfg, display.x_window, NULL );
   if ( egl.egl_surface == EGL_NO_SURFACE ) {
      printf("Unable to create EGL surface eglError: %i \n",eglGetError());
      return 1;
   }
 
   //// egl-contexts collect all state descriptions needed required for operation
   EGLint ctxattr[] = {
      EGL_CONTEXT_CLIENT_VERSION, 2,
      EGL_NONE
   };
   egl.egl_context = eglCreateContext ( egl.egl_display, ecfg, EGL_NO_CONTEXT, ctxattr );
   if ( egl.egl_context == EGL_NO_CONTEXT ) {
      printf("Unable to create EGL context eglError: %i \n" , eglGetError());
      return 1;
   }
 
   //// associate the egl-context with the egl-surface
   eglMakeCurrent( egl.egl_display, egl.egl_surface, egl.egl_surface, egl.egl_context );
 
   glViewport ( 0 , 0 , 100 , 100 );
   glClearColor ( 0.0f , 1.0f , 0.07f , 1.0f);    // background color
   glClear ( GL_COLOR_BUFFER_BIT );
 
   eglSwapBuffers ( egl.egl_display, egl.egl_surface );  // get the rendered buffer to the screen

   sleep(1); 

   eglDestroyContext ( egl.egl_display, egl.egl_context );
   eglDestroySurface ( egl.egl_display, egl.egl_surface );
   eglTerminate      ( egl.egl_display );
   XDestroyWindow    ( display.x_display, display.x_window );
   XCloseDisplay     ( display.x_display );
 
   return 0;
}	
