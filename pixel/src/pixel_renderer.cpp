#include "pixel_renderer.h"

PixelRenderer::PixelRenderer()
{
	generateCanvas(this->xSize, this->ySize);	
}

void PixelRenderer::generateCanvas(const GLuint& xSize, const GLuint& ySize)
{
	struct timeval startRenderTime, endRenderTime, endEventTime;
	gettimeofday(&startRenderTime, NULL);
	this->xSize = xSize;
	this->ySize = ySize;
	GLfloat dx = 2.0f / xSize;
	GLfloat dy = 2.0f / ySize; 
	this->buffer.clear();

	auto addZandColor=[&buffer = this->buffer, dx=dx, dy=dy](GLuint x, GLuint y, int shift){
			double s = (double)shift;
			double off = 0.1f;
			buffer.push_back(0.0f);
			buffer.push_back(off + s * 0.5f);
			buffer.push_back(off + s * 0.5f);
			buffer.push_back(off + s * 0.5f);
			buffer.push_back(1.0f);	
	};

	for(GLuint x=0; x<this->xSize; x++)
	{
		// 4.   x     x 3. 6.        
		//       .
		//        .
		//         .
		//          .
		//           .
		// 1. 5.x     x 2.
		for (GLuint y=0; y<this->ySize; y++)
		{
			// 1
			this->buffer.push_back(dx * (x + borderPercent) - 1);
	 		this->buffer.push_back(dy * (y + borderPercent) - 1);
		
			addZandColor(x,y,0);
			// 2
			this->buffer.push_back(dx * (x + 1 - borderPercent) - 1);
	 		this->buffer.push_back(dy * (y + borderPercent) - 1);

			addZandColor(x,y,0);
			// 3	
			this->buffer.push_back(dx * (x + 1 - borderPercent) - 1);
	 		this->buffer.push_back(dy * (y + 1 - borderPercent)  - 1);
			
			addZandColor(x,y,1);	
			// 4
			this->buffer.push_back(dx * (x + borderPercent) - 1);
	 		this->buffer.push_back(dy * (y + 1 - borderPercent) - 1);

			addZandColor(x,y,1);
			// 5
			this->buffer.push_back(dx * (x + borderPercent) - 1);
	 		this->buffer.push_back(dy * (y + borderPercent) - 1);

			addZandColor(x,y,0);
			// 6
			this->buffer.push_back(dx * (x + 1 - borderPercent) - 1);
	 		this->buffer.push_back(dy * (y + 1 - borderPercent)  - 1);
			
			addZandColor(x,y,1);	
		}
	}
	gettimeofday(&endRenderTime, NULL);
	std::cout << "generate canvas time " << (endRenderTime.tv_usec - startRenderTime.tv_usec) << std::endl;	
}

void PixelRenderer::render(const std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager, const std::unique_ptr<PixelSurface>& pixelSurface) 
{

	struct timeval startRenderTime, endRenderTime, endEventTime;

	gettimeofday(&startRenderTime, NULL);
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
	gettimeofday(&endRenderTime, NULL);
	std::cout << "opengl render time " << (endRenderTime.tv_usec - startRenderTime.tv_usec) << std::endl;	
	return;
}
