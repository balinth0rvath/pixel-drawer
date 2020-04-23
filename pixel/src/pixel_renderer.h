#pragma once
#include "src/pixel_common_headers.h"
#include "src/pixel_gl_program_manager.h"
#include "src/pixel_surface.h"
#include "src/pixel_animation.h"

class PixelRenderer {
public:
	PixelRenderer();
	void render(const std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager, const std::unique_ptr<PixelSurface>& pixelSurface);
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
	
	std::unique_ptr<PixelAnimation> pixelAnimation = nullptr;

private:
	void generateVertexBufferMatrix();
	void generateVertexBufferSphere();
	void generateVertexBuffers();
	inline void addPixel(const GLuint& x, const GLuint& y);
	inline void addZandColor(const GLuint& x, const GLuint& y, const GLuint& shift);
	inline void changePixelColor(const GLuint& x, const GLuint& y, const GLuint& color);
	inline void changePixelShadow(const GLuint& x, const GLuint& y, const GLuint& shadowColor);
	inline GLfloat getRed(const GLuint& color);
	inline GLfloat getGreen(const GLuint& color);
	inline GLfloat getBlue(const GLuint& color);
	GLuint xSize = 64;
	GLuint ySize = 36;
	GLfloat dx = 0.0f;
	GLfloat dy = 0.0f;
	
	std::vector<GLuint> colorBuffer;
	std::vector<GLfloat> vertexBufferMatrix;
	std::vector<GLfloat> vertexBufferSphere;
	
	GLuint sphereVisible = 1;

	GLfloat borderPercent=0.05;
	GLuint backgroundColor = 0x0;
	GLuint cursorColor = 0x333333;
	GLuint shadowColor = 0x000000;
	GLfloat mag = 2.8;


};

