#pragma once
#include "pixel_common_headers.h"

class PixelSurface {
public:
	PixelSurface();
	void initEGL();
	void closeEGL();
	const EGLDisplay getEGLDisplay() { return this->eglDisplay; };
	const EGLSurface getEGLSurface() { return this->eglSurface; };
	PixelSurface(const PixelSurface& s) = delete;
	PixelSurface(PixelSurface&& s) = delete;
	PixelSurface& operator=(const PixelSurface& s) = delete;
	PixelSurface& operator=(PixelSurface&& s) = delete;
	~PixelSurface();

	GLuint windowWidth=700;
	GLuint windowHeight=700;

	// TODO port 
#ifdef IMX6
	wl_display* display;
#else
	Display* display;
#endif // IMX6
protected:
#ifdef IMX6
	wl_compositor *compositor;
	wl_shell *shell;
	wl_registry* registry;
	wl_egl_window * window;
	wl_surface * surface;
	wl_shell_surface* shell_surface;
#else
	Window window;
#endif // IMX6
private: 
	virtual void initDisplayClient() = 0;
	virtual void closeDisplayClient() = 0;
	void logConfigs();
	EGLDisplay eglDisplay;
	std::vector<EGLConfig> configs;
	EGLContext	eglContext;
	EGLSurface 	eglSurface;
	EGLint major;
	EGLint minor;

	std::vector<EGLint> attribList;
};
