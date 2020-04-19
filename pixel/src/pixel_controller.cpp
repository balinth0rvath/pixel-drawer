#include "src/pixel_controller.h"

PixelController::PixelController(std::unique_ptr<PixelRenderer>& pixelRenderer,
								std::unique_ptr<PixelSurface>& pixelSurface,
								std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager) :
								pixelRenderer(pixelRenderer),
								pixelSurface(pixelSurface),
								pixelGLProgramManager(pixelGLProgramManager)
						
{

}

void PixelController::eventLoop()
{
	struct timeval startRenderTime, endRenderTime, endEventTime;
	int shouldStop=0;
	
	pixelRenderer->drawPixel(5,3,0x0000ff);
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
				if (e.xkey.keycode==114)
				{
					pixelRenderer->clearPixel(5,3);
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

}
