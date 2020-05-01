#include "pixel_surface.h"

PixelSurface::PixelSurface() {
	this->attribList = { 
	EGL_RED_SIZE, 8,
	EGL_GREEN_SIZE, 8,
	EGL_BLUE_SIZE, 8,
	EGL_ALPHA_SIZE, 8,
	EGL_DEPTH_SIZE, 8,
	EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
	EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
	EGL_NONE};
}

PixelSurface::~PixelSurface() {};

void PixelSurface::logConfigs()
{
	std::map<std::string,EGLint> attribMap = {
		{"EGL_CONFIG_ID", EGL_CONFIG_ID},
		{"EGL_BUFFER_SIZE", EGL_BUFFER_SIZE},
		{"EGL_RED_SIZE", EGL_RED_SIZE},
		{"EGL_GREEN_SIZE", EGL_GREEN_SIZE},
		{"EGL_BLUE_SIZE", EGL_BLUE_SIZE},
		{"EGL_LUMINANCE_SIZE", EGL_LUMINANCE_SIZE},
		{"EGL_ALPHA_SIZE", EGL_ALPHA_SIZE},
		{"EGL_ALPHA_MASK_SIZE", EGL_ALPHA_MASK_SIZE},
		{"EGL_BIND_TO_TEXTURE_RGB", EGL_BIND_TO_TEXTURE_RGB},
		{"EGL_BIND_TO_TEXTURE_RGBA", EGL_BIND_TO_TEXTURE_RGBA},
		{"EGL_COLOR_BUFFER_TYPE", EGL_COLOR_BUFFER_TYPE},
		{"EGL_CONFIG_CAVEAT", EGL_CONFIG_CAVEAT},
		{"EGL_CONFORMANT", EGL_CONFORMANT},
		{"EGL_DEPTH_SIZE", EGL_DEPTH_SIZE},
		{"EGL_LEVEL", EGL_LEVEL},
		{"EGL_MAX_PBUFFER_WIDTH", EGL_MAX_PBUFFER_WIDTH},
		{"EGL_MAX_PBUFFER_HEIGHT", EGL_MAX_PBUFFER_HEIGHT},
		{"EGL_MAX_PBUFFER_PIXELS", EGL_MAX_PBUFFER_PIXELS},
		{"EGL_MAX_SWAP_INTERVAL", EGL_MAX_SWAP_INTERVAL},
		{"EGL_MIN_SWAP_INTERVAL", EGL_MIN_SWAP_INTERVAL},
		{"EGL_NATIVE_RENDERABLE", EGL_NATIVE_RENDERABLE},
		{"EGL_NATIVE_VISUAL_ID", EGL_NATIVE_VISUAL_ID},
		{"EGL_NATIVE_VISUAL_TYPE", EGL_NATIVE_VISUAL_TYPE},
		{"EGL_RENDERABLE_TYPE", EGL_RENDERABLE_TYPE},
		{"EGL_SAMPLE_BUFFERS", EGL_SAMPLE_BUFFERS},
		{"EGL_SAMPLES", EGL_SAMPLES},
		{"EGL_STENCIL_SIZE", EGL_STENCIL_SIZE},
		{"EGL_SURFACE_TYPE", EGL_SURFACE_TYPE},
		{"EGL_TRANSPARENT_TYPE", EGL_TRANSPARENT_TYPE},
		{"EGL_TRANSPARENT_RED_VALUE", EGL_TRANSPARENT_RED_VALUE},
		{"EGL_TRANSPARENT_GREEN_VALUE", EGL_TRANSPARENT_GREEN_VALUE},
		{"EGL_TRANSPARENT_BLUE_VALUE", EGL_TRANSPARENT_BLUE_VALUE}
		
	};
	std::sort(this->configs.begin(), this->configs.end());
	for(const auto& config : this->configs)
	{
		for(const auto& attrib :attribMap )
		{ 
			EGLint value;
			eglGetConfigAttrib(this->eglDisplay, config, attrib.second, &value);
			std::cout << attrib.first << ": " << value << std::endl;
		}
		//getchar();
	}

}

void PixelSurface::initEGL() {

	initDisplayClient();
    this->eglDisplay  =  eglGetDisplay( (EGLNativeDisplayType) this->display );
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
	std::cout << "Max configs: " << maxConfigs << std::endl;

	this->configs.resize(maxConfigs);  

    if ( !eglChooseConfig( this->eglDisplay, &this->attribList.front(), &this->configs.front(), maxConfigs, &numConfigs ) ) {
		GLenum e = glGetError();
		printf("Error choosing egl configs: %i num configs: %i \n", e, numConfigs); 
		exit(1);
    }

	std::cout << "Available confis: " << numConfigs << std::endl;
	this->configs.resize(numConfigs);  

	logConfigs();

    this->eglSurface = eglCreateWindowSurface ( this->eglDisplay, this->configs.front(), this->window, NULL );
    if ( this->eglSurface == EGL_NO_SURFACE ) {
      std::cout << "Unable to create EGL surface eglError: " << eglGetError() << std::endl;
      exit(1);
   }
   EGLint ctxattr[] = {
      EGL_CONTEXT_CLIENT_VERSION, 2,
      EGL_NONE
   };
   this->eglContext = eglCreateContext ( this->eglDisplay, this->configs.front(), EGL_NO_CONTEXT, ctxattr );
   if ( this->eglContext == EGL_NO_CONTEXT ) {
      std::cout << "Unable to create EGL context eglError: " << eglGetError << std::endl;
      exit(1);
   }
 
   eglMakeCurrent( this->eglDisplay, this->eglSurface, this->eglSurface, this->eglContext );

};

void PixelSurface::closeEGL()
{
  	eglDestroyContext ( this->eglDisplay, this->eglContext );
 	eglDestroySurface ( this->eglDisplay, this->eglSurface );
  	eglTerminate      ( this->eglDisplay );

	closeDisplayClient();
};



