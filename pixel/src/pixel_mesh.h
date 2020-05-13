#pragma once
#include "pixel_common_headers.h"
#include "pixel_palette.h"

class PixelMesh {
public:
	PixelMesh(	PixelPalette* const pixelPalette, 
				const GLuint& xSize, 
				const GLuint& ySize);

	void generateVertexBufferMatrix(std::vector<GLfloat>* const vertexBufferMatrix,
									std::vector<GLuint>* const colorBuffer,	
									const GLuint& xSize,
									const GLuint& ySize);
	void generateVertexBufferSphere(std::vector<GLfloat>* const vertexBufferSphere);
	void generateIndexBufferSphere(std::vector<GLubyte>* const indexBufferSphere);
	PixelPalette* const pixelPalette;
	void addVertex(	std::vector<GLfloat>* const vertexBufferMatrix,
					std::vector<GLuint>* const colorBuffer,	
					const GLuint& x, 
					const GLuint& y,
					const GLuint& xSize,
					const GLuint& ySize
);
private:
	const GLfloat sphereSize = 1.0f;	
	inline void addZandColor(std::vector<GLfloat>* const vertexBufferMatrix,
							const GLuint& x, 
							const GLuint& y, 
							const GLuint& color);

	GLfloat mag = 2.8;
	GLfloat borderPercent=0.05;
	GLfloat dx = 0.0f;
	GLfloat dy = 0.0f;

};
