#pragma once
#include "src/pixel_common_headers.h"
#include "src/pixel_palette.h"
#include "src/pixel_gl_program_manager.h"
#include "src/pixel_surface.h"
#include "src/pixel_animation.h"

class PixelRenderer {
public:
	PixelRenderer(std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager, std::unique_ptr<PixelSurface>& pixelSurface, std::unique_ptr<PixelPalette>& pixelPalette);
	void render();
	void drawPixel(const GLuint& x, const GLuint& y, const GLuint& color);
	void clearPixel(const GLuint& x, const GLuint& y);
	void focusPixel(const GLuint& x, const GLuint& y);
	void unfocusPixel(const GLuint& x, const GLuint& y);

	void generateCanvas(const GLuint& xSize, const GLuint& ySize, const GLuint& backgroundColor);
	void generateSphere(const std::unique_ptr<PixelSurface>& pixelSurface);
	inline GLuint getXSize() { return this->xSize; };
	inline GLuint getYSize() { return this->ySize; };
	void setSphereVisible();
	void setSphereInvisible();
	void changeSphereVisibility();
	
	std::unique_ptr<PixelAnimation> pixelAnimation;
	const std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager;
	const std::unique_ptr<PixelSurface>& pixelSurface;
	const std::unique_ptr<PixelPalette>& pixelPalette;

private:
	inline void changePixelColor(const GLuint& x, const GLuint& y, const GLuint& color);
	inline void changePixelShadow(const GLuint& x, const GLuint& y, const GLuint& shadowColor);
	GLuint xSize = 64;
	GLuint ySize = 36;
	
	std::vector<GLuint> colorBuffer;
	std::vector<GLfloat> vertexBufferMatrix;
	std::vector<GLfloat> vertexBufferSphere;
	std::vector<GLubyte> indexBufferSphere;
	const GLfloat sphereSize = 1.0f;	
	GLuint sphereVisible = 1;
	

	GLuint backgroundColor = 0x0;
	GLuint cursorColor = 0x333333;
	GLuint shadowColor = 0x000000;

	// to pixel_mesh 
	GLfloat mag = 2.8;
	GLfloat borderPercent=0.05;
	GLfloat dx = 0.0f;
	GLfloat dy = 0.0f;
	void generateVertexBufferMatrix();
	void generateVertexBufferSphere();
	inline void addPixel(const GLuint& x, const GLuint& y);
	inline void addZandColor(const GLuint& x, const GLuint& y, const GLuint& shift);
	inline GLfloat getRed(const GLuint& color);
	inline GLfloat getGreen(const GLuint& color);
	inline GLfloat getBlue(const GLuint& color);


};

