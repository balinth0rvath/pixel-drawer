#include <memory>
#include "src/pixel_gl_program_manager.h"
#include "src/pixel_surface.h"

class PixelRenderer {
public:
	void render(const std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager, const std::unique_ptr<PixelSurface>& pixelSurface);
private:
	void generateCanvas(const GLuint& xSize, const GLuint& ySize);
	GLuint xSize = 64;
	GLuint ySize = 36;
	
	std::vector<GLfloat> buffer;
	GLfloat borderPercent=0.0;
};

