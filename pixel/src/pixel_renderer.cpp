#include "pixel_renderer.h"

PixelRenderer::PixelRenderer(	PixelGLProgramManager* const pixelGLProgramManager, 
								PixelSurface* const pixelSurface, 
								PixelPalette* const pixelPalette) :
	pixelGLProgramManager(pixelGLProgramManager),
	pixelSurface(pixelSurface),
	pixelPalette(pixelPalette)
{
	this->pixelMesh = std::make_unique<PixelMesh>(this->pixelPalette, xSize, ySize);	
}


void PixelRenderer::generateSphere(PixelSurface* const pixelSurface)
{
	this->pixelAnimation = 
		std::make_unique<PixelAnimation>(pixelSurface->windowWidth, pixelSurface->windowHeight);
	this->vertexBufferSphere = std::make_unique<std::vector<GLfloat>>(0);
	this->indexBufferSphere = std::make_unique<std::vector<GLubyte>>(0);
	this->pixelMesh->generateVertexBufferSphere(vertexBufferSphere.get());
	this->pixelMesh->generateIndexBufferSphere(indexBufferSphere.get());
	
}

void PixelRenderer::generateCanvas() 
{
	this->colorBuffer = std::make_unique<std::vector<GLuint>>( xSize * ySize, backgroundColor );
	this->vertexBufferMatrix = std::make_unique<std::vector<GLfloat>>();	
	this->pixelMesh->generateVertexBufferMatrix(vertexBufferMatrix.get(), 
												colorBuffer.get(), 
												xSize, 
												ySize);	
}

void PixelRenderer::setColorBuffer(std::vector<GLuint>* const copyBuffer)
{
	(*this->colorBuffer) = *copyBuffer;
	repaint();
}

void PixelRenderer::getColorBuffer(std::vector<GLuint>* const copyBuffer) const
{
	*copyBuffer = (*this->colorBuffer);
}

void PixelRenderer::repaint()
{
	for(GLuint y=0; y < this->ySize; ++y)
		for(GLuint x=0; x < this->xSize; ++x)
		{
			GLuint index = y * this->xSize + x;
			changePixelColor(x,y,(*colorBuffer)[index]);
		}
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
	(*this->vertexBufferMatrix)[offset + 3 + 0*7] = PixelPalette::getRed(color);
	(*this->vertexBufferMatrix)[offset + 3 + 1*7] = PixelPalette::getRed(color);
	(*this->vertexBufferMatrix)[offset + 3 + 4*7] = PixelPalette::getRed(color);
	(*this->vertexBufferMatrix)[offset + 4 + 0*7] = PixelPalette::getGreen(color);
	(*this->vertexBufferMatrix)[offset + 4 + 1*7] = PixelPalette::getGreen(color);
	(*this->vertexBufferMatrix)[offset + 4 + 4*7] = PixelPalette::getGreen(color);
	(*this->vertexBufferMatrix)[offset + 5 + 0*7] = PixelPalette::getBlue(color);
	(*this->vertexBufferMatrix)[offset + 5 + 1*7] = PixelPalette::getBlue(color);
	(*this->vertexBufferMatrix)[offset + 5 + 4*7] = PixelPalette::getBlue(color);
}

void PixelRenderer::changePixelColor(const GLuint& x, const GLuint& y, const GLuint& color)
{
	int offset = ((y * this->xSize) + x) *  6 * 7;
	(*this->vertexBufferMatrix)[offset + 3 + 2*7] = PixelPalette::getRed(color);
	(*this->vertexBufferMatrix)[offset + 3 + 3*7] = PixelPalette::getRed(color);
	(*this->vertexBufferMatrix)[offset + 3 + 5*7] = PixelPalette::getRed(color);
	(*this->vertexBufferMatrix)[offset + 4 + 2*7] = PixelPalette::getGreen(color);
	(*this->vertexBufferMatrix)[offset + 4 + 3*7] = PixelPalette::getGreen(color);
	(*this->vertexBufferMatrix)[offset + 4 + 5*7] = PixelPalette::getGreen(color);
	(*this->vertexBufferMatrix)[offset + 5 + 2*7] = PixelPalette::getBlue(color);
	(*this->vertexBufferMatrix)[offset + 5 + 3*7] = PixelPalette::getBlue(color);
	(*this->vertexBufferMatrix)[offset + 5 + 5*7] = PixelPalette::getBlue(color);
}

void PixelRenderer::drawPixel(const GLuint& x, const GLuint& y, const GLuint& color)
{
	GLuint index = y * this->xSize + x;

	(*this->colorBuffer)[index] = color;
	changePixelColor(x,y,color);
}

void PixelRenderer::togglePixel(const GLuint& x, const GLuint& y, const GLuint& color)
{
	GLuint index = y * this->xSize + x;

	if ((*this->colorBuffer)[index] == this->backgroundColor)
	{ 
		(*this->colorBuffer)[index] = color;
		changePixelColor(x,y,color);
	} else
	{
		(*this->colorBuffer)[index] = this->backgroundColor;
		changePixelColor(x,y,this->backgroundColor);
	}
}

void PixelRenderer::clearPixel(const GLuint& x, const GLuint& y)
{
	(*this->colorBuffer)[y * this->xSize + x] = backgroundColor;
	changePixelColor(x,y,this->backgroundColor);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 28, &((*this->vertexBufferMatrix)[0]));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 28, &((*this->vertexBufferMatrix)[0])+3);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glm::mat4 baseModel(1.0f);
	glm::mat4 noProjection(1.0f);
	glUniformMatrix4fv(pixelGLProgramManager->getUniformModel(), 1, GL_FALSE, glm::value_ptr(baseModel));
	glUniformMatrix4fv(pixelGLProgramManager->getUniformProjection(), 1, GL_FALSE, glm::value_ptr(pixelAnimation->getSphereProjection()));

	glDrawArrays(GL_TRIANGLES, 0, 6 * this->xSize * this->ySize);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 28, &((*this->vertexBufferSphere)[0]));
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 28, &((*this->vertexBufferSphere)[0])+3);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glm::mat4 sphereModel(1.0f);
	pixelAnimation->animateSphere();
	sphereModel = glm::translate(sphereModel, pixelAnimation->getSpherePosition());

	sphereModel = glm::rotate(sphereModel, getSphereAngleAlpha(),  glm::vec3(1.0f,0.0f,0.0f));
	sphereModel = glm::rotate(sphereModel, getSphereAngleZeta(), glm::vec3(0.0f,0.0f,1.0f));
	glUniformMatrix4fv(pixelGLProgramManager->getUniformModel(), 1, GL_FALSE, glm::value_ptr(sphereModel));
	glUniformMatrix4fv(pixelGLProgramManager->getUniformProjection(), 1, GL_FALSE, glm::value_ptr(pixelAnimation->getSphereProjection()));
	glDrawElements(GL_TRIANGLES, 6 *  72, GL_UNSIGNED_BYTE, &((*this->indexBufferSphere)[0]));


	eglSwapBuffers ( pixelSurface->getEGLDisplay(), pixelSurface->getEGLSurface() );  // get the rendered vertexBufferMatrix to the screen
	return;
}

void PixelRenderer::incAlpha(const GLfloat& dRotation) 
{ 
	sphereAngleAlpha += dRotation; 
	if (sphereAngleAlpha > 180)
	{
		sphereAngleAlpha = 180;	
	}
	show(); 
};

void PixelRenderer::decAlpha(const GLfloat& dRotation) 
{ 
	sphereAngleAlpha -= dRotation; 
	if (sphereAngleAlpha < 0)
	{
		sphereAngleAlpha = 0; 
	} 
	show(); 
};

void PixelRenderer::incZeta(const GLfloat& dRotation) 
{ 
	sphereAngleZeta += dRotation; 
	if (sphereAngleZeta == 360)
	{
		sphereAngleZeta = 0;	
	}
	show(); 
};

void PixelRenderer::decZeta(const GLfloat& dRotation) 
{ 
	sphereAngleZeta -= dRotation; 
	if (sphereAngleZeta < 0)
	{
		sphereAngleZeta = 330; 
	} 
	show(); 
};

GLuint PixelRenderer::getMainColorIndex() const
{
	GLuint z = sphereAngleZeta / 30;
	GLuint idx = (z<4) ? 3 - z : 15 - z;
	return idx;
}
	
GLuint PixelRenderer::getSubColorIndex() const
{
	GLuint a = sphereAngleAlpha / 30;
	return a + 1;
}

GLuint PixelRenderer::checkCursorBounds(const GLuint& cursorX, const GLuint& cursorY) const
{
	return (cursorX <= this->xSize && cursorY <= this->ySize);
}
