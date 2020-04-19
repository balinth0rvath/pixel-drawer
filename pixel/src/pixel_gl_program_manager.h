#pragma once
#include "pixel_common_headers.h"

class PixelGLProgramManager {

public:
	PixelGLProgramManager();
	const GLuint getProgramObject() { return this->programObject; };
	const int init();
	
private:
	GLuint programObject;
	
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
	
	const GLuint loadShader(const GLenum& type, const std::string& source);	
	void initShaders();
};

