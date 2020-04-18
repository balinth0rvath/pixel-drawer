#include <memory>
#include <unistd.h>
#include <sys/time.h>
#include "src/pixel_gl_program_manager.h"
#include "src/pixel_surface.h"

class PixelRenderer {
public:
	PixelRenderer();
	void render(const std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager, const std::unique_ptr<PixelSurface>& pixelSurface);
	inline void addPixel(const int& x, const int& y);
private:
	void generateCanvas();
	inline void addZandColor(const GLuint& x, const GLuint& y, const int& shift);
	GLuint xSize = 64;
	GLuint ySize = 36;
	GLfloat dx = 0.0f;
	GLfloat dy = 0.0f;
	
	std::vector<GLfloat> buffer;
	GLfloat borderPercent=0.05;
};

