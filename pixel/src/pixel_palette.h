#pragma once
#include "src/pixel_common_headers.h"

class PixelPalette {
public:
	PixelPalette();
	GLfloat getRed(const GLubyte& alpha, const GLubyte& zeta);
	GLfloat getGreen(const GLubyte& alpha, const GLubyte& zeta);
	GLfloat getBlue(const GLubyte& alpha, const GLubyte& zeta);
private:
	inline GLubyte convertZeta(const GLubyte& zeta);
	std::unique_ptr<std::vector<std::vector<GLuint>>> palette;  
};
