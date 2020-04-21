#include "pixel_renderer.h"

PixelRenderer::PixelRenderer()
{
}

void PixelRenderer::generateCanvas(const GLuint & xSize, const GLuint& ySize, const GLuint& backgroundColor) 
{
	this->xSize = xSize;
	this->ySize = ySize;
	this->dx = 2.0f / this->xSize;
	this->dy = 2.0f / this->ySize;
	this->colorBuffer = std::vector<GLuint>( xSize * ySize, backgroundColor );
	this->backgroundColor = backgroundColor;
	generateVertexBuffers();	

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
	this->vertexBufferMatrix.push_back(dx * (x + borderPercent) - 1);
	this->vertexBufferMatrix.push_back(dy * (y + borderPercent) - 1);

	addZandColor(x,y,0);
	// 1
	this->vertexBufferMatrix.push_back(dx * (x + 1 - borderPercent) - 1);
	this->vertexBufferMatrix.push_back(dy * (y + borderPercent) - 1);

	addZandColor(x,y,0);
	// 2	
	this->vertexBufferMatrix.push_back(dx * (x + 1 - borderPercent) - 1);
	this->vertexBufferMatrix.push_back(dy * (y + 1 - borderPercent)  - 1);
	
	addZandColor(x,y,this->colorBuffer[ x + y * this->xSize]);	
	// 3
	this->vertexBufferMatrix.push_back(dx * (x + borderPercent) - 1);
	this->vertexBufferMatrix.push_back(dy * (y + 1 - borderPercent) - 1);

	addZandColor(x,y,this->colorBuffer[ x + y * this->xSize]);
	// 4
	this->vertexBufferMatrix.push_back(dx * (x + borderPercent) - 1);
	this->vertexBufferMatrix.push_back(dy * (y + borderPercent) - 1);

	addZandColor(x,y,0);
	// 5
	this->vertexBufferMatrix.push_back(dx * (x + 1 - borderPercent) - 1);
	this->vertexBufferMatrix.push_back(dy * (y + 1 - borderPercent)  - 1);
	
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
	this->vertexBufferMatrix.push_back(0.0f);
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
	//this->vertexBufferSphere = std::vector<GLfloat>(0);
	
	this->vertexBufferSphere = {0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
								1.0f, 1.0f,-1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
								1.0f, 0.0f,-1.0f, 0.0f, 0.0f, 1.0f, 1.0f};
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


void PixelRenderer::render(const std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager, const std::unique_ptr<PixelSurface>& pixelSurface) 
{
	glViewport ( 0 , 0 , pixelSurface->windowWidth , pixelSurface->windowHeight );
	glClearColor ( 0.1f , 0.1f , 0.1f , 0.1f);    // background color
	glClear ( GL_COLOR_BUFFER_BIT );
	glUseProgram(pixelGLProgramManager->getProgramObject());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 28, &vertexBufferMatrix[0]);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 28, &vertexBufferMatrix[0]+3);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 6 * this->xSize * this->ySize);

	if (sphereVisible)
	{
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 28, &vertexBufferSphere[0]);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 28, &vertexBufferSphere[0]+3);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_TRIANGLES, 0, 3 );

	} 

	eglSwapBuffers ( pixelSurface->getEGLDisplay(), pixelSurface->getEGLSurface() );  // get the rendered vertexBufferMatrix to the screen
	return;
}
