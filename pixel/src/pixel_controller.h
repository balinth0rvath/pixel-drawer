#include "src/pixel_common_headers.h"
#include "src/pixel_renderer.h"

#define X11_KEY_UP 		0x6f
#define X11_KEY_LEFT 	0x71
#define X11_KEY_RIGHT 	0x72
#define X11_KEY_DOWN 	0x74
#define X11_SPACE 		0x41
#define X11_ESC 		0x09

class PixelController {
public:
	PixelController(std::unique_ptr<PixelRenderer>& pixelRenderer,
					std::unique_ptr<PixelSurface>& pixelSurface,
					std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager);

	void eventLoop();
private:
	void processKeyCode(const int& keycode, int& shouldStop);
	const std::unique_ptr<PixelRenderer>& pixelRenderer;
	const std::unique_ptr<PixelSurface>& pixelSurface;
	const std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager;

	GLuint cursorX=0;
	GLuint cursorY=0;
	const GLuint cursorColor = 0xffff00;
};


