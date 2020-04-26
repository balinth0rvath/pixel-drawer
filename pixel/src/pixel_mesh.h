#pragma once
#include "pixel_common_headers.h"
#include "pixel_palette.h"

class PixelMesh {
public:
	PixelMesh(	const std::unique_ptr<PixelPalette>& pixelPalette, 
				const GLuint& xSize, 
				const GLuint& ySize);

	void generateVertexBufferMatrix(const std::unique_ptr<std::vector<GLfloat>>& vertexBufferMatrix,
									const std::unique_ptr<std::vector<GLuint>>& colorBuffer,	
									const GLuint& xSize,
									const GLuint& ySize);
	void generateVertexBufferSphere(const std::unique_ptr<std::vector<GLfloat>>& vertexBufferSphere);
	void generateIndexBufferSphere(const std::unique_ptr<std::vector<GLubyte>>& indexBufferSphere);
	const std::unique_ptr<PixelPalette>& pixelPalette;
	void addVertex(	const std::unique_ptr<std::vector<GLfloat>>& vertexBufferMatrix,
					const std::unique_ptr<std::vector<GLuint>>& colorBuffer,	
					const GLuint& x, 
					const GLuint& y,
					const GLuint& xSize,
					const GLuint& ySize
);
private:
	const GLfloat sphereSize = 1.0f;	
	inline void addZandColor(const std::unique_ptr<std::vector<GLfloat>>& vertexBufferMatrix,
							const GLuint& x, 
							const GLuint& y, 
							const GLuint& color);

	GLfloat mag = 2.8;
	GLfloat borderPercent=0.05;
	GLfloat dx = 0.0f;
	GLfloat dy = 0.0f;

};
