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

	GLuint windowWidth=1360;
	GLuint windowHeight=800;
	Display* xDisplay;

private: 
	void initDisplayClient();
	void closeDisplayClient();
	void logConfigs();
	Window xWindow;

	EGLDisplay eglDisplay;
	std::vector<EGLConfig> configs;
	EGLContext	eglContext;
	EGLSurface 	eglSurface;
	EGLint major;
	EGLint minor;

	std::vector<EGLint> attribList;
};
