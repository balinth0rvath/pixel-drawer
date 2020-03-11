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
 
Display    *x_display;
Window      win;
EGLDisplay  egl_display;
EGLContext  egl_context;
EGLSurface  egl_surface;
 
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
 
   x_display = XOpenDisplay ( NULL ); 
   if ( x_display == NULL ) {
      printf("cannot connect to X server \n");
      return 1;
   }
 
   Window root  =  DefaultRootWindow( x_display );
 
   XSetWindowAttributes  swa;
   swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask;
 
   win  =  XCreateWindow (   // create a window with the provided parameters
              x_display, root,
              0, 0, 800, 480,   0,
              CopyFromParent, InputOutput,
              CopyFromParent, CWEventMask,
              &swa );
 
   XSetWindowAttributes  xattr;
   Atom  atom;
   int   one = 1;
 
   xattr.override_redirect = False;
   XChangeWindowAttributes ( x_display, win, CWOverrideRedirect, &xattr );
 
   atom = XInternAtom ( x_display, "_NET_WM_STATE_FULLSCREEN", True );
   XChangeProperty (
      x_display, win,
      XInternAtom ( x_display, "_NET_WM_STATE", True ),
      XA_ATOM,  32,  PropModeReplace,
      (unsigned char*) &atom,  1 );
 
   XChangeProperty (
      x_display, win,
      XInternAtom ( x_display, "_HILDON_NON_COMPOSITED_WINDOW", False ),
      XA_INTEGER,  32,  PropModeReplace,
      (unsigned char*) &one,  1);
 
   XWMHints hints;
   hints.input = True;
   hints.flags = InputHint;
   XSetWMHints(x_display, win, &hints);
 
   XMapWindow ( x_display , win );             // make the window visible on the screen
   XStoreName ( x_display , win , "GL test" ); // give the window a name
 
   //// get identifiers for the provided atom name strings
   Atom wm_state   = XInternAtom ( x_display, "_NET_WM_STATE", False );
   Atom fullscreen = XInternAtom ( x_display, "_NET_WM_STATE_FULLSCREEN", False );
 
   XEvent xev;
   memset ( &xev, 0, sizeof(xev) );
 
   xev.type                 = ClientMessage;
   xev.xclient.window       = win;
   xev.xclient.message_type = wm_state;
   xev.xclient.format       = 32;
   xev.xclient.data.l[0]    = 1;
   xev.xclient.data.l[1]    = fullscreen;
   XSendEvent (                // send an event mask to the X-server
      x_display,
      DefaultRootWindow ( x_display ),
      False,
      SubstructureNotifyMask,
      &xev );
 
   egl_display  =  eglGetDisplay( (EGLNativeDisplayType) x_display );
   if ( egl_display == EGL_NO_DISPLAY ) {
      printf("Got no EGL display.");
      return 1;
   }
 
   if ( !eglInitialize( egl_display, NULL, NULL ) ) {
      printf("Unable to initialize EGL");
      return 1;
   }
 

 
   EGLConfig  ecfg;
   EGLint     num_config;
   if ( !eglChooseConfig( egl_display, attr, &ecfg, 1, &num_config ) ) {
      printf("Failed to choose config eglError: %i \n", eglGetError());
      return 1;
   }
 
   if ( num_config != 1 ) {
      printf("Didn't get exactly one config, but  %i \n", num_config);
      return 1;
   }
 
   egl_surface = eglCreateWindowSurface ( egl_display, ecfg, win, NULL );
   if ( egl_surface == EGL_NO_SURFACE ) {
      printf("Unable to create EGL surface eglError: %i \n",eglGetError());
      return 1;
   }
 
   //// egl-contexts collect all state descriptions needed required for operation
   EGLint ctxattr[] = {
      EGL_CONTEXT_CLIENT_VERSION, 2,
      EGL_NONE
   };
   egl_context = eglCreateContext ( egl_display, ecfg, EGL_NO_CONTEXT, ctxattr );
   if ( egl_context == EGL_NO_CONTEXT ) {
      printf("Unable to create EGL context eglError: %i \n" , eglGetError());
      return 1;
   }
 
   //// associate the egl-context with the egl-surface
   eglMakeCurrent( egl_display, egl_surface, egl_surface, egl_context );
 
   glViewport ( 0 , 0 , 700 , 500 );
   glClearColor ( 0.0f , 1.0f , 0.07f , 1.0f);    // background color
   glClear ( GL_COLOR_BUFFER_BIT );
 
   eglSwapBuffers ( egl_display, egl_surface );  // get the rendered buffer to the screen

   sleep(1); 
   ////  cleaning up...
   eglDestroyContext ( egl_display, egl_context );
   eglDestroySurface ( egl_display, egl_surface );
   eglTerminate      ( egl_display );
   XDestroyWindow    ( x_display, win );
   XCloseDisplay     ( x_display );
 
   return 0;
}	
