#include "pixel_renderer.h"

void PixelRenderer::generateCanvas(const GLfloat& borderPercent, const GLuint& xSize, const GLuint& ySize)
{
	this->xSize = xSize;
	this->ySize = ySize;
	GLfloat dx = 2.0f / xSize;
	GLfloat dy = 2.0f / ySize; 
	this->buffer.clear();

	auto addZandColor=[&buffer = this->buffer, dx=dx, dy=dy](GLuint x, GLuint y){
			buffer.push_back(0.0f);
			buffer.push_back((dx * x + dy * y) / 2.0);
			buffer.push_back(dx * x);
			buffer.push_back(dy * y);
			buffer.push_back(1);	
	};

	for(GLuint x=0; x<this->xSize; x++)
		for (GLuint y=0; y<this->ySize; y++)
		{
			this->buffer.push_back(dx * (x + borderPercent) - 1);
	 		this->buffer.push_back(dy * (y + borderPercent) - 1);

			addZandColor(x,y);

			this->buffer.push_back(dx * (x + 1 - borderPercent) - 1);
	 		this->buffer.push_back(dy * (y + borderPercent) - 1);

			addZandColor(x,y);

			this->buffer.push_back(dx * (x + 1 - borderPercent) - 1);
	 		this->buffer.push_back(dy * (y + 1 - borderPercent)  - 1);
			
			addZandColor(x,y);	

			this->buffer.push_back(dx * (x + borderPercent) - 1);
	 		this->buffer.push_back(dy * (y + 1 - borderPercent) - 1);

			addZandColor(x,y);

			this->buffer.push_back(dx * (x + borderPercent) - 1);
	 		this->buffer.push_back(dy * (y + borderPercent) - 1);

			addZandColor(x,y);

			this->buffer.push_back(dx * (x + 1 - borderPercent) - 1);
	 		this->buffer.push_back(dy * (y + 1 - borderPercent)  - 1);
			
			addZandColor(x,y);	
		}
}

void PixelRenderer::render(const std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager, const std::unique_ptr<PixelSurface>& pixelSurface) 
{
	buffer = { -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
							1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
							0.0f,-1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};

	generateCanvas(pixelSurface->borderPercent, this->xSize, this->ySize);	
	glViewport ( 0 , 0 , pixelSurface->windowWidth , pixelSurface->windowHeight );
	glClearColor ( 0.1f , 0.1f , 0.1f , 0.1f);    // background color
	glClear ( GL_COLOR_BUFFER_BIT );
	glUseProgram(pixelGLProgramManager->getProgramObject());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 28, &buffer[0]);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 28, &buffer[0]+3);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 7 * this->xSize * this->ySize);
	eglSwapBuffers ( pixelSurface->getEGLDisplay(), pixelSurface->getEGLSurface() );  // get the rendered buffer to the screen
	return;
}
