#include "pixel_mesh.h"

PixelMesh::PixelMesh(	const std::unique_ptr<PixelPalette>& pixelPalette, 
						const GLuint& xSize, 
						const GLuint& ySize)
	: pixelPalette(pixelPalette)
{
	this->dx =  2.0f / xSize;
	this->dy =  2.0f / ySize;
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

void PixelMesh::generateVertexBufferMatrix(	
								const std::unique_ptr<std::vector<GLfloat>>& vertexBufferMatrix,
								const std::unique_ptr<std::vector<GLuint>>& colorBuffer, 
								const GLuint& xSize, 		
								const GLuint& ySize)
{
	for(GLuint y=0; y < ySize; y++)
	{
		for (GLuint x=0; x < xSize; x++)
		{
			addVertex(vertexBufferMatrix, colorBuffer, x,y,xSize,ySize);
		}
	}
}

void PixelMesh::addVertex(	const std::unique_ptr<std::vector<GLfloat>>& vertexBufferMatrix,
							const std::unique_ptr<std::vector<GLuint>>& colorBuffer,	
							const GLuint& x, 
							const GLuint& y,
							const GLuint& xSize,
							const GLuint& ySize)
{
	// 3.   x     x 2. 5.        
	//           . 
	//          . 
	//         .
	//        .  
	//       .    
	// 0. 4.x     x 1.

	// 0
	vertexBufferMatrix->push_back(mag * dx * (x + borderPercent) - mag);
	vertexBufferMatrix->push_back(mag * dy * (y + borderPercent) - mag);

	addZandColor(vertexBufferMatrix,x,y,0);
	// 1
	vertexBufferMatrix->push_back(mag * dx * (x + 1 - borderPercent) - mag);
	vertexBufferMatrix->push_back(mag * dy * (y + borderPercent) - mag);

	addZandColor(vertexBufferMatrix,x,y,0);
	// 2	
	vertexBufferMatrix->push_back(mag * dx * (x + 1 - borderPercent) - mag);
	vertexBufferMatrix->push_back(mag * dy * (y + 1 - borderPercent)  - mag);
	
	addZandColor(vertexBufferMatrix,x,y,(*colorBuffer)[ x + y * xSize]);	
	// 3
	vertexBufferMatrix->push_back(mag * dx * (x + borderPercent) - mag);
	vertexBufferMatrix->push_back(mag * dy * (y + 1 - borderPercent) - mag);

	addZandColor(vertexBufferMatrix,x,y,(*colorBuffer)[ x + y * xSize]);
	// 4
	vertexBufferMatrix->push_back(mag * dx * (x + borderPercent) - mag);
	vertexBufferMatrix->push_back(mag * dy * (y + borderPercent) - mag);

	addZandColor(vertexBufferMatrix,x,y,0);
	// 5
	vertexBufferMatrix->push_back(mag * dx * (x + 1 - borderPercent) - mag);
	vertexBufferMatrix->push_back(mag * dy * (y + 1 - borderPercent)  - mag);
	
	addZandColor(vertexBufferMatrix,x,y,(*colorBuffer)[ x + y * xSize]);	

}

inline void PixelMesh::addZandColor(const std::unique_ptr<std::vector<GLfloat>>& vertexBufferMatrix,
									const GLuint& x, 		
									const GLuint& y, 
									const GLuint& color)
{
	vertexBufferMatrix->push_back(-5.0f);
	vertexBufferMatrix->push_back(PixelPalette::getRed(color));
	vertexBufferMatrix->push_back(PixelPalette::getGreen(color));
	vertexBufferMatrix->push_back(PixelPalette::getBlue(color));
	vertexBufferMatrix->push_back(1.0f);	
}


