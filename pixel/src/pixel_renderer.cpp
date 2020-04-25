#include "pixel_renderer.h"

PixelRenderer::PixelRenderer(std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager, std::unique_ptr<PixelSurface>& pixelSurface, std::unique_ptr<PixelPalette>& pixelPalette) :
	pixelGLProgramManager(pixelGLProgramManager),
	pixelSurface(pixelSurface),
	pixelPalette(pixelPalette)
{
}


void PixelRenderer::generateSphere(const std::unique_ptr<PixelSurface>& pixelSurface)
{
	this->pixelAnimation = std::make_unique<PixelAnimation>(pixelSurface);
	generateVertexBufferSphere();
}

void PixelRenderer::generateCanvas(const GLuint & xSize, const GLuint& ySize, const GLuint& backgroundColor) 
{
	this->xSize = xSize;
	this->ySize = ySize;
	this->dx =  2.0f / this->xSize;
	this->dy =  2.0f / this->ySize;
	this->colorBuffer = std::vector<GLuint>( xSize * ySize, backgroundColor );
	this->backgroundColor = backgroundColor;
	generateVertexBufferMatrix();	

}

inline void PixelRenderer::addPixel(const GLuint& x, const GLuint& y)
{
	// 3.   x     x 2. 5.        
	//           . 
	//          . 
	//         .
	//        .  
	//       .    
	// 0. 4.x     x 1.

	// 0
	this->vertexBufferMatrix.push_back(mag * dx * (x + borderPercent) - mag);
	this->vertexBufferMatrix.push_back(mag * dy * (y + borderPercent) - mag);

	addZandColor(x,y,0);
	// 1
	this->vertexBufferMatrix.push_back(mag * dx * (x + 1 - borderPercent) - mag);
	this->vertexBufferMatrix.push_back(mag * dy * (y + borderPercent) - mag);

	addZandColor(x,y,0);
	// 2	
	this->vertexBufferMatrix.push_back(mag * dx * (x + 1 - borderPercent) - mag);
	this->vertexBufferMatrix.push_back(mag * dy * (y + 1 - borderPercent)  - mag);
	
	addZandColor(x,y,this->colorBuffer[ x + y * this->xSize]);	
	// 3
	this->vertexBufferMatrix.push_back(mag * dx * (x + borderPercent) - mag);
	this->vertexBufferMatrix.push_back(mag * dy * (y + 1 - borderPercent) - mag);

	addZandColor(x,y,this->colorBuffer[ x + y * this->xSize]);
	// 4
	this->vertexBufferMatrix.push_back(mag * dx * (x + borderPercent) - mag);
	this->vertexBufferMatrix.push_back(mag * dy * (y + borderPercent) - mag);

	addZandColor(x,y,0);
	// 5
	this->vertexBufferMatrix.push_back(mag * dx * (x + 1 - borderPercent) - mag);
	this->vertexBufferMatrix.push_back(mag * dy * (y + 1 - borderPercent)  - mag);
	
	addZandColor(x,y,this->colorBuffer[ x + y * this->xSize]);	

}
void PixelRenderer::focusPixel(const GLuint& x, const GLuint& y)
{
	changePixelShadow(x,y,this->cursorColor);
}
void PixelRenderer::unfocusPixel(const GLuint& x, const GLuint& y)
{
	changePixelShadow(x,y,this->shadowColor);
}
	
void PixelRenderer::changePixelShadow(const GLuint& x, const GLuint& y, const GLuint& color)
{
	int offset = ((y * this->xSize) + x) *  6 * 7;
	this->vertexBufferMatrix[offset + 3 + 0*7] = getRed(color);
	this->vertexBufferMatrix[offset + 3 + 1*7] = getRed(color);
	this->vertexBufferMatrix[offset + 3 + 4*7] = getRed(color);
	this->vertexBufferMatrix[offset + 4 + 0*7] = getGreen(color);
	this->vertexBufferMatrix[offset + 4 + 1*7] = getGreen(color);
	this->vertexBufferMatrix[offset + 4 + 4*7] = getGreen(color);
	this->vertexBufferMatrix[offset + 5 + 0*7] = getBlue(color);
	this->vertexBufferMatrix[offset + 5 + 1*7] = getBlue(color);
	this->vertexBufferMatrix[offset + 5 + 4*7] = getBlue(color);
}

void PixelRenderer::changePixelColor(const GLuint& x, const GLuint& y, const GLuint& color)
{
	int offset = ((y * this->xSize) + x) *  6 * 7;
	this->vertexBufferMatrix[offset + 3 + 2*7] = getRed(color);
	this->vertexBufferMatrix[offset + 3 + 3*7] = getRed(color);
	this->vertexBufferMatrix[offset + 3 + 5*7] = getRed(color);
	this->vertexBufferMatrix[offset + 4 + 2*7] = getGreen(color);
	this->vertexBufferMatrix[offset + 4 + 3*7] = getGreen(color);
	this->vertexBufferMatrix[offset + 4 + 5*7] = getGreen(color);
	this->vertexBufferMatrix[offset + 5 + 2*7] = getBlue(color);
	this->vertexBufferMatrix[offset + 5 + 3*7] = getBlue(color);
	this->vertexBufferMatrix[offset + 5 + 5*7] = getBlue(color);
}

void PixelRenderer::drawPixel(const GLuint& x, const GLuint& y, const GLuint& color)
{
	GLuint index = y * this->xSize + x;

	if (this->colorBuffer[index] == this->backgroundColor)
	{ 
		this->colorBuffer[index] = color;
		changePixelColor(x,y,color);
	} else
	{
		this->colorBuffer[index] = this->backgroundColor;
		changePixelColor(x,y,this->backgroundColor);
	}
}

void PixelRenderer::clearPixel(const GLuint& x, const GLuint& y)
{
	this->colorBuffer[y * this->xSize + x] = backgroundColor;
	changePixelColor(x,y,this->backgroundColor);
}

inline GLfloat PixelRenderer::getRed(const GLuint& color)
{
	GLuint tmp = color >> 16;
	uint8_t red = (uint8_t) tmp;
	return (GLfloat)red / 0xff;
}

inline GLfloat PixelRenderer::getGreen(const GLuint& color)
{
	GLuint tmp = (color >> 8) & 0xff;
	uint8_t green = (uint8_t) tmp;
	return (GLfloat)green / 0xff;
}

inline GLfloat PixelRenderer::getBlue(const GLuint& color)
{
	uint8_t blue = (uint8_t) (color & 0xff);
	return (GLfloat)blue / 0xff;
}

inline void PixelRenderer::addZandColor(const GLuint& x, const GLuint& y, const GLuint& color)
{
	this->vertexBufferMatrix.push_back(-5.0f);
	this->vertexBufferMatrix.push_back(getRed(color));
	this->vertexBufferMatrix.push_back(getGreen(color));
	this->vertexBufferMatrix.push_back(getBlue(color));
	this->vertexBufferMatrix.push_back(1.0f);	
}

void PixelRenderer::generateVertexBufferMatrix()
{
	this->vertexBufferMatrix = std::vector<GLfloat>(0); 

	for(GLuint y=0; y<this->ySize; y++)
	{
		for (GLuint x=0; x<this->xSize; x++)
		{
			addPixel(x,y);
		}
	}
}

void PixelRenderer::generateVertexBufferSphere()
{
	this->vertexBufferSphere = std::vector<GLfloat>(0);
	this->indexBufferSphere = std::vector<GLubyte>(0);

	for(GLuint invert = 0; invert < 2; ++invert)
		for(GLuint zetaIndex = 0; zetaIndex<4; ++zetaIndex)
			for(GLuint alphaIndex =0; alphaIndex<12; ++alphaIndex)
			{
				GLfloat x = sphereSize * cos((GLfloat)alphaIndex * 2 * M_PI / 12.0f) * 
										 cos((GLfloat)zetaIndex * M_PI / 6.0f);
				this->vertexBufferSphere.push_back(x);

				GLfloat y = sphereSize * sin((GLfloat)alphaIndex * 2 * M_PI / 12.0f) *
										 cos((GLfloat)zetaIndex * M_PI / 6.0f);
				this->vertexBufferSphere.push_back(y);

				GLfloat z = sphereSize * sin((GLfloat)zetaIndex * M_PI / 6.0f);
				if (invert)
					this->vertexBufferSphere.push_back(-1.0f * z);
				else
					this->vertexBufferSphere.push_back(z);
		

				this->vertexBufferSphere.push_back(
					pixelPalette->getRed(alphaIndex, zetaIndex + invert * 4));
				this->vertexBufferSphere.push_back(
					pixelPalette->getGreen(alphaIndex, zetaIndex + invert * 4));
				this->vertexBufferSphere.push_back(
					pixelPalette->getBlue(alphaIndex, zetaIndex + invert * 4));
					
				this->vertexBufferSphere.push_back(1.0f);


			}

	for (GLuint invert = 0; invert < 2; ++invert)
		for (GLuint zetaIndex = 0; zetaIndex<3; ++zetaIndex)
			for (GLuint alphaIndex = 0; alphaIndex<12; ++alphaIndex)
			{
				GLuint invertOffset = invert * 48;
				GLuint overflowAlphaIndex = (alphaIndex==11) ? 0 : alphaIndex + 1;			

				this->indexBufferSphere.push_back(invertOffset +
						12 * zetaIndex + alphaIndex);

				this->indexBufferSphere.push_back(invertOffset +
						12 * zetaIndex + overflowAlphaIndex);

				this->indexBufferSphere.push_back(invertOffset +
						12 * (zetaIndex + 1 ) + alphaIndex);

				this->indexBufferSphere.push_back(invertOffset +
						12 * zetaIndex + overflowAlphaIndex);

				this->indexBufferSphere.push_back(invertOffset +
						12 * (zetaIndex + 1 ) + alphaIndex );

				this->indexBufferSphere.push_back(invertOffset +
						12 * (zetaIndex + 1 ) + overflowAlphaIndex );

		}
	
}

void PixelRenderer::generateVertexBuffers()
{
	generateVertexBufferMatrix();
	generateVertexBufferSphere();
}

void PixelRenderer::setSphereVisible()
{
	this->sphereVisible = 1;
}

void PixelRenderer::setSphereInvisible()
{
	this->sphereVisible = 1;
}

void PixelRenderer::changeSphereVisibility()
{
	this->sphereVisible = !this->sphereVisible;
}


void PixelRenderer::render() 
{
	glViewport ( 0 , 0 , pixelSurface->windowWidth , pixelSurface->windowHeight );
	glClearColor ( 0.1f , 0.1f , 0.1f , 0.1f);    // background color

	glEnable(GL_DEPTH_TEST);

	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glUseProgram(pixelGLProgramManager->getProgramObject());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 28, &vertexBufferMatrix[0]);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 28, &vertexBufferMatrix[0]+3);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glm::mat4 baseModel(1.0f);
	glm::mat4 noProjection(1.0f);
	glUniformMatrix4fv(pixelGLProgramManager->getUniformModel(), 1, GL_FALSE, glm::value_ptr(baseModel));
	glUniformMatrix4fv(pixelGLProgramManager->getUniformProjection(), 1, GL_FALSE, glm::value_ptr(pixelAnimation->getSphereProjection()));

	glDrawArrays(GL_TRIANGLES, 0, 6 * this->xSize * this->ySize);

	if (sphereVisible)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 28, &vertexBufferSphere[0]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 28, &vertexBufferSphere[0]+3);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glm::mat4 sphereModel(1.0f);
		pixelAnimation->animateSphere();
		sphereModel = glm::translate(sphereModel, pixelAnimation->getSpherePosition());
		sphereModel = glm::rotate(sphereModel, pixelAnimation->getSphereRotation(), glm::vec3(1.0f,1.0f,0.0f));
		pixelAnimation->rotateSphere();
		glUniformMatrix4fv(pixelGLProgramManager->getUniformModel(), 1, GL_FALSE, glm::value_ptr(sphereModel));
		glUniformMatrix4fv(pixelGLProgramManager->getUniformProjection(), 1, GL_FALSE, glm::value_ptr(pixelAnimation->getSphereProjection()));
		glDrawElements(GL_TRIANGLES, 6 *  72, GL_UNSIGNED_BYTE, &indexBufferSphere[0]);

	} 

	eglSwapBuffers ( pixelSurface->getEGLDisplay(), pixelSurface->getEGLSurface() );  // get the rendered vertexBufferMatrix to the screen
	return;
}
