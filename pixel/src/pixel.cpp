#include "src/pixel_common_headers.h"
#include "src/pixel_surface.h"
#include "src/pixel_gl_program_manager.h"
#include "src/pixel_renderer.h"
#include "src/pixel_controller.h"

int  main()
{
	auto pixelGLProgramManager = std::make_unique<PixelGLProgramManager>();
	auto pixelSurface = std::make_unique<PixelSurface>();

	auto pixelRenderer = std::make_unique<PixelRenderer>(pixelSurface);
	auto pixelController = std::make_unique<PixelController>(
								pixelRenderer, 
								pixelSurface,
								pixelGLProgramManager);

	pixelSurface->initEGL();
	pixelGLProgramManager->init();

	if (!pixelGLProgramManager->getProgramObject())
		return 1;

	pixelRenderer->generateCanvas(32,32, 0x202020);
	pixelController->eventLoop();
	pixelSurface->closeEGL();

	return 0;
}	
