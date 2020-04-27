#pragma once
#include "src/pixel_common_headers.h"

class PixelPalette {
public:
	PixelPalette();
	GLuint getColor(const GLubyte& zeta, const GLubyte& alpha);
	GLfloat getRed(const GLubyte& alpha, const GLubyte& zeta);
	GLfloat getGreen(const GLubyte& alpha, const GLubyte& zeta);
	GLfloat getBlue(const GLubyte& alpha, const GLubyte& zeta);
	static GLfloat getRed(const GLuint& color);
	static GLfloat getGreen(const GLuint& color);
	static GLfloat getBlue(const GLuint& color);
private:
	inline GLubyte convertZeta(const GLubyte& zeta);
	std::unique_ptr<std::vector<std::vector<GLuint>>> palette;  
};
