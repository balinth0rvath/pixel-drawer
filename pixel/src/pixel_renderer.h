#pragma once
#include "src/pixel_common_headers.h"
#include "src/pixel_gl_program_manager.h"
#include "src/pixel_surface.h"

class PixelRenderer {
public:
	PixelRenderer();
	void render(const std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager, const std::unique_ptr<PixelSurface>& pixelSurface);
	void drawPixel(const GLuint& x, const GLuint& y, const GLuint& color);
	void clearPixel(const GLuint& x, const GLuint& y);
	void generateCanvas(const GLuint& xSize, const GLuint& ySize, const GLuint& backgroundColor);
private:
	void generateVertexBuffer();
	inline void addPixel(const GLuint& x, const GLuint& y);
	inline void addZandColor(const GLuint& x, const GLuint& y, const GLuint& shift);

	inline GLfloat getRed(const GLuint& color);
	inline GLfloat getGreen(const GLuint& color);
	inline GLfloat getBlue(const GLuint& color);
	GLuint xSize = 64;
	GLuint ySize = 36;
	GLfloat dx = 0.0f;
	GLfloat dy = 0.0f;
	
	std::vector<GLuint> colorBuffer;
	std::vector<GLfloat> vertexBuffer;
	
	GLfloat borderPercent=0.05;
	GLuint backgroundColor = 0x0;
};

