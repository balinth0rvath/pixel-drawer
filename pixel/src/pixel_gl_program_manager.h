#pragma once
#include "pixel_common_headers.h"

class PixelGLProgramManager {

public:
	PixelGLProgramManager();
	const GLuint getProgramObject() { return this->programObject; };
	const GLuint getUniformModel() { return this->uniformModel; };
	const GLuint getUniformProjection() { return this->uniformProjection; };
	const int init();
	
private:
	GLuint programObject;
	GLuint uniformModel;	
	GLuint uniformProjection;	
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
	
	const GLuint loadShader(const GLenum& type, const std::string& source);	
	void initShaders();
};

