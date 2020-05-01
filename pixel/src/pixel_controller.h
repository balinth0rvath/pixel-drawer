#include "src/pixel_common_headers.h"
#include "src/pixel_file_manager.h"
#include "src/pixel_renderer.h"
#include "src/pixel_animation.h"

#define X11_KEY_UP 		0x6f
#define X11_KEY_LEFT 	0x71
#define X11_KEY_RIGHT 	0x72
#define X11_KEY_DOWN 	0x74
#define X11_SPACE 		0x41
#define X11_ESC 		0x09
#define X11_KEY_1		0x0a
#define X11_KEY_2		0x0b
#define X11_KEY_3		0x0c
#define X11_KEY_4		0x0d
#define X11_KEY_5		0x0e
#define X11_KEY_6		0x0f
#define X11_KEY_7		0x10
#define X11_KEY_8		0x11
#define X11_KEY_9		0x12

class PixelController {
public:
	PixelController(std::unique_ptr<PixelRenderer>& pixelRenderer,
					std::unique_ptr<PixelSurface>& pixelSurface,
					std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager,
					std::unique_ptr<PixelPalette>& pixelPalette,
					std::unique_ptr<PixelFileManager>& pixelFileManager);

	void eventLoop();
private:
	void processKeyCode(const int& keycode);
	void processButton( const int& pointerX, 
						const int& pointerY, 		
						const int& button);
	const std::unique_ptr<PixelRenderer>& pixelRenderer;
	const std::unique_ptr<PixelSurface>& pixelSurface;
	const std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager;
	const std::unique_ptr<PixelPalette>& pixelPalette;
	const std::unique_ptr<PixelFileManager>& pixelFileManager;

	int shouldStop=0;

	GLuint cursorX=0;
	GLuint cursorY=0;
	GLuint currentColor=0x0;
	GLuint currentFile=1;
	GLuint dRotation = 30;
	GLuint buttonPressed = 0;
};


