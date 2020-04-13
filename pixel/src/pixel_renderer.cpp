#include "pixel_renderer.h"

void PixelRenderer::render(const std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager, const std::unique_ptr<PixelSurface>& pixelSurface) 
{
	GLfloat vertices[] = { -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
							1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
							0.0f,-1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f};
	glViewport ( 0 , 0 , 100 , 100 );
	glClearColor ( 0.0f , 1.0f , 0.07f , 1.0f);    // background color
	glClear ( GL_COLOR_BUFFER_BIT );
	glUseProgram(pixelGLProgramManager->getProgramObject());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 28, vertices);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 28, vertices+3);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	eglSwapBuffers ( pixelSurface->getEGLDisplay(), pixelSurface->getEGLSurface() );  // get the rendered buffer to the screen
	return;
}
