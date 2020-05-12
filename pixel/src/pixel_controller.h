#pragma once
#include "src/pixel_common_headers.h"
#include "src/pixel_file_manager.h"
#include "src/pixel_renderer.h"
#include "src/pixel_animation.h"

#ifdef IMX6

#define KEY_UP 		0x67
#define KEY_LEFT 	0x69
#define KEY_RIGHT 	0x6a
#define KEY_DOWN 	0x6c
#define SPACE 		0x39
#define ESC 		0x01
#define KEY_1		0x02
#define KEY_2		0x03
#define KEY_3		0x04
#define KEY_4		0x05
#define KEY_5		0x06
#define KEY_6		0x07
#define KEY_7		0x08
#define KEY_8		0x09
#define KEY_9		0x0a
#else
#define KEY_UP 		0x6f
#define KEY_LEFT 	0x71
#define KEY_RIGHT 	0x72
#define KEY_DOWN 	0x74
#define SPACE 		0x41
#define ESC 		0x09
#define KEY_1		0x0a
#define KEY_2		0x0b
#define KEY_3		0x0c
#define KEY_4		0x0d
#define KEY_5		0x0e
#define KEY_6		0x0f
#define KEY_7		0x10
#define KEY_8		0x11
#define KEY_9		0x12

#endif //IMX6

class PixelController {
public:
	PixelController(std::unique_ptr<PixelRenderer>& pixelRenderer,
					std::unique_ptr<PixelSurface>& pixelSurface,
					std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager,
					std::unique_ptr<PixelPalette>& pixelPalette,
					std::unique_ptr<PixelFileManager>& pixelFileManager);

	void eventLoop();
	void processKeyCode(const int& keycode);
	void processButton( const int& pointerX, 
						const int& pointerY, 		
						const int& button);
private:
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


