#pragma once
#include "pixel_common_headers.h"
#include "pixel_palette.h"

class PixelMesh {
public:
	PixelMesh(const std::unique_ptr<PixelPalette>& pixelPalette);

	void generateVertexBufferSphere(const std::unique_ptr<std::vector<GLfloat>>& vertexBufferSphere);
	void generateIndexBufferSphere(const std::unique_ptr<std::vector<GLubyte>>& indexBufferSphere);
	const std::unique_ptr<PixelPalette>& pixelPalette;
private:
	const GLfloat sphereSize = 1.0f;	

};
