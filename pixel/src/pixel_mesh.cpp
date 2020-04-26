#include "pixel_mesh.h"

PixelMesh::PixelMesh(const std::unique_ptr<PixelPalette>& pixelPalette)
	: pixelPalette(pixelPalette)
{

}


void PixelMesh::generateVertexBufferSphere(const std::unique_ptr<std::vector<GLfloat>>& vertexBufferSphere)
{
	for(GLuint invert = 0; invert < 2; ++invert)
		for(GLuint zetaIndex = 0; zetaIndex<4; ++zetaIndex)
			for(GLuint alphaIndex =0; alphaIndex<12; ++alphaIndex)
			{
				GLfloat x = sphereSize * cos((GLfloat)alphaIndex * 2 * M_PI / 12.0f) * 
										 cos((GLfloat)zetaIndex * M_PI / 6.0f);
				vertexBufferSphere->push_back(x);

				GLfloat y = sphereSize * sin((GLfloat)alphaIndex * 2 * M_PI / 12.0f) *
										 cos((GLfloat)zetaIndex * M_PI / 6.0f);
				vertexBufferSphere->push_back(y);

				GLfloat z = sphereSize * sin((GLfloat)zetaIndex * M_PI / 6.0f);
				if (invert)
					vertexBufferSphere->push_back(-1.0f * z);
				else
					vertexBufferSphere->push_back(z);
		

				vertexBufferSphere->push_back(
					pixelPalette->getRed(alphaIndex, zetaIndex + invert * 4));
				vertexBufferSphere->push_back(
					pixelPalette->getGreen(alphaIndex, zetaIndex + invert * 4));
				vertexBufferSphere->push_back(
					pixelPalette->getBlue(alphaIndex, zetaIndex + invert * 4));
					
				vertexBufferSphere->push_back(1.0f);

			}
}

void PixelMesh::generateIndexBufferSphere(const std::unique_ptr<std::vector<GLubyte>>& indexBufferSphere)
{
	for (GLuint invert = 0; invert < 2; ++invert)
		for (GLuint zetaIndex = 0; zetaIndex<3; ++zetaIndex)
			for (GLuint alphaIndex = 0; alphaIndex<12; ++alphaIndex)
			{
				GLuint invertOffset = invert * 48;
				GLuint overflowAlphaIndex = (alphaIndex==11) ? 0 : alphaIndex + 1;			

				indexBufferSphere->push_back(invertOffset +
						12 * zetaIndex + alphaIndex);

				indexBufferSphere->push_back(invertOffset +
						12 * zetaIndex + overflowAlphaIndex);

				indexBufferSphere->push_back(invertOffset +
						12 * (zetaIndex + 1 ) + alphaIndex);

				indexBufferSphere->push_back(invertOffset +
						12 * zetaIndex + overflowAlphaIndex);

				indexBufferSphere->push_back(invertOffset +
						12 * (zetaIndex + 1 ) + alphaIndex );

				indexBufferSphere->push_back(invertOffset +
						12 * (zetaIndex + 1 ) + overflowAlphaIndex );

		}
}
