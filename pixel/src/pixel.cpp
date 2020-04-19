#include "src/pixel_common_headers.h"
#include "src/pixel_surface.h"
#include "src/pixel_gl_program_manager.h"
#include "src/pixel_renderer.h"


int  main()
{
	auto pixelGLProgramManager = std::make_unique<PixelGLProgramManager>();
	auto pixelSurface = std::make_unique<PixelSurface>();

	struct timeval startRenderTime, endRenderTime, endEventTime;
	auto pixelRenderer = std::make_unique<PixelRenderer>();

	pixelSurface->initEGL();
	pixelGLProgramManager->init();

	if (!pixelGLProgramManager->getProgramObject())
		return 1;

	int shouldStop=0;
	
	for (;!shouldStop;)
	{
		gettimeofday(&startRenderTime, NULL);
		pixelRenderer->render(pixelGLProgramManager, pixelSurface);
		gettimeofday(&endRenderTime, NULL);
		while (XPending(pixelSurface->xDisplay))
		{
			XEvent e;
			XNextEvent(pixelSurface->xDisplay, &e);
			switch (e.type)
			{
				case 2:
		
				std::cout << "Keycode: " << e.xkey.keycode << std::endl;
				if (e.xkey.keycode==9)
				{
					shouldStop=1;
				}	
				break;
			
				case 6:
				std::cout << "mouse event: " << e.type << std::endl;
				break;

				default:
				break;

			}
		}
		gettimeofday(&endEventTime, NULL);
		std::cout << " outer Elapsed render time: " << (endRenderTime.tv_usec - startRenderTime.tv_usec) << std::endl;

		std::cout << "Elapsed event time: " << (endEventTime.tv_usec - endRenderTime.tv_usec) << std::endl;

	}
	
	pixelSurface->closeEGL();

	return 0;
}	
