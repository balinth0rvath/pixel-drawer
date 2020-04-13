#pragma once
#include "GLES2/gl2.h"
#include <string>
#include <iostream>

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

