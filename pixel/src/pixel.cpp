#include "src/pixel_common_headers.h"
#include "src/pixel_palette.h"
#include "src/pixel_file_manager.h"
#include "src/pixel_surface.h"
#include "src/pixel_surface_x11.h"
#include "src/pixel_gl_program_manager.h"
#include "src/pixel_renderer.h"
#include "src/pixel_controller.h"

int  main()
{
	auto pixelFileManager = std::make_unique<PixelFileManager>();
	auto pixelGLProgramManager = std::make_unique<PixelGLProgramManager>();
	std::unique_ptr<PixelSurface> pixelSurface = std::make_unique<PixelSurfaceX11>();
	auto pixelPalette = std::make_unique<PixelPalette>();
	auto pixelRenderer = std::make_unique<PixelRenderer>(
								pixelGLProgramManager, 
								pixelSurface, 		
								pixelPalette);
	auto pixelController = std::make_unique<PixelController>(
								pixelRenderer, 
								pixelSurface,
								pixelGLProgramManager,
								pixelPalette,
								pixelFileManager);


	pixelSurface->initEGL();
	pixelGLProgramManager->init();

	if (!pixelGLProgramManager->getProgramObject())
		return 1;


	pixelRenderer->generateCanvas();
	pixelRenderer->generateSphere(pixelSurface);
	pixelController->eventLoop();
	pixelSurface->closeEGL();

	return 0;
}	
