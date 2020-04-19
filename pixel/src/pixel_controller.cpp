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
	struct timeval startRenderTime, endRenderTime;
	int shouldStop=0;

	uint8_t counter=0;
	uint32_t sumRenderTime=0;
		
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
		
		counter++;
		uint32_t start = startRenderTime.tv_usec; 	
		uint32_t end = endRenderTime.tv_usec; 	
		if (end > start)
		{
			sumRenderTime+=	(end - start);
		}
		
		if (!counter)
		{
			counter=0;
			double fps = 1000000.0f / (double)(sumRenderTime >> 8);
			std::cout << "Render time: " << (sumRenderTime >> 8) << " usec" << " FPS: " << fps << std::endl;
			sumRenderTime = 0;		
		}

	}

}
