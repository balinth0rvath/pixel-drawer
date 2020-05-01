#include "pixel_surface_x11.h"


void PixelSurfaceX11::initDisplayClient() {
    this->display = XOpenDisplay ( NULL ); 

    if ( this->display == NULL ) {
		std::cout << "cannot connect to display server " << std::endl;
		exit(1);
    }
 
    Window root  =  DefaultRootWindow( this->display );
 
    XSetWindowAttributes  swa;
    swa.event_mask  =  ExposureMask | PointerMotionMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask; 
 
    this->window  = XCreateWindow (   // create a window with the provided parameters
		this->display, 
		root,
		0, 0, 
		this->windowWidth, this->windowHeight,   
		0,
		CopyFromParent, 
		InputOutput,
		CopyFromParent, 
		CWEventMask,
		&swa );
 
   XMapWindow ( this->display , this->window );             // make the window visible on the screen

   XStoreName ( this->display , this->window , "example" ); // give the window a name

};

void PixelSurfaceX11::closeDisplayClient()
{
   XDestroyWindow    ( this->display, this->window );
   XCloseDisplay     ( this->display );
};
