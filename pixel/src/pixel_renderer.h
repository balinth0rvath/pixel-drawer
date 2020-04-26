#pragma once
#include "src/pixel_common_headers.h"
#include "src/pixel_palette.h"
#include "src/pixel_gl_program_manager.h"
#include "src/pixel_surface.h"
#include "src/pixel_animation.h"
#include "src/pixel_mesh.h"

class PixelRenderer {
public:
	PixelRenderer(std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager, std::unique_ptr<PixelSurface>& pixelSurface, std::unique_ptr<PixelPalette>& pixelPalette);
	void render();
	void drawPixel(const GLuint& x, const GLuint& y, const GLuint& color);
	void clearPixel(const GLuint& x, const GLuint& y);
	void focusPixel(const GLuint& x, const GLuint& y);
	void unfocusPixel(const GLuint& x, const GLuint& y);

	void generateCanvas();
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
	void incAlpha(const GLfloat& dRotation) { sphereAngleAlpha += dRotation;};
	void decAlpha(const GLfloat& dRotation) { sphereAngleAlpha -= dRotation;};
	void incZeta(const GLfloat& dRotation) { sphereAngleZeta += dRotation;};
	void decZeta(const GLfloat& dRotation) { sphereAngleZeta -= dRotation;};
private:
	std::unique_ptr<PixelMesh> pixelMesh;
	inline void changePixelColor(const GLuint& x, const GLuint& y, const GLuint& color);
	inline void changePixelShadow(const GLuint& x, const GLuint& y, const GLuint& shadowColor);
	GLuint xSize = 32;
	GLuint ySize = 32;
	
	std::unique_ptr<std::vector<GLuint>> colorBuffer;
	std::unique_ptr<std::vector<GLfloat>> vertexBufferMatrix;
	std::unique_ptr<std::vector<GLfloat>> vertexBufferSphere;
	std::unique_ptr<std::vector<GLubyte>> indexBufferSphere;

	GLuint sphereVisible = 1;	
	GLfloat sphereAngleAlpha = 0.0f;
	GLfloat sphereAngleZeta = 0.0f;
		
	GLuint backgroundColor = 0x202020;
	GLuint cursorColor = 0x333333;
	GLuint shadowColor = 0x000000;

};

