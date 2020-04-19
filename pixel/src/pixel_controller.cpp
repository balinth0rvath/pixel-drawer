#include "src/pixel_controller.h"

PixelController::PixelController(std::unique_ptr<PixelRenderer>& pixelRenderer,
								std::unique_ptr<PixelSurface>& pixelSurface,
								std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager) :
								pixelRenderer(pixelRenderer),
								pixelSurface(pixelSurface),
								pixelGLProgramManager(pixelGLProgramManager)
						
{

}

void PixelController::processKeyCode(const int& keycode, int& shouldStop)
{
	switch (keycode)
	{
		case X11_ESC:
			shouldStop=1;
			break;
		case X11_SPACE:
			pixelRenderer->clearPixel(cursorX,cursorY);
			break;
		case X11_KEY_UP:
			if (this->pixelRenderer->getYSize()-1 > cursorY) 
			{ 
				pixelRenderer->clearPixel(cursorX,cursorY);
				cursorY+= 1; 
				pixelRenderer->drawPixel(cursorX,cursorY,cursorColor);
			}
			break;
		case X11_KEY_DOWN:
			if (cursorY != 0)
			{
				pixelRenderer->clearPixel(cursorX,cursorY);
				cursorY-= 1;
				pixelRenderer->drawPixel(cursorX,cursorY,cursorColor);
			}
			break;
		case X11_KEY_LEFT:
			if (cursorX != 0)
			{
				pixelRenderer->clearPixel(cursorX,cursorY);
				cursorX-= 1;
				pixelRenderer->drawPixel(cursorX,cursorY,cursorColor);
			}
			break;
		case X11_KEY_RIGHT:
			if (this->pixelRenderer->getXSize()-1 > cursorX)
			{
				pixelRenderer->clearPixel(cursorX,cursorY);
				cursorX+= 1;
				pixelRenderer->drawPixel(cursorX,cursorY,cursorColor);
			}
			break;
		default:
			break;
	}
}

void PixelController::eventLoop()
{
	struct timeval startRenderTime, endRenderTime;
	int shouldStop=0;

	uint8_t counter=0;
	uint32_t sumRenderTime=0;
		
	pixelRenderer->drawPixel(cursorX,cursorY,cursorColor);
	for (;!shouldStop;)
	{
		gettimeofday(&startRenderTime, NULL);
		pixelRenderer->render(pixelGLProgramManager, pixelSurface);
		gettimeofday(&endRenderTime, NULL);
		while (XPending(pixelSurface->xDisplay))
		{
			XEvent e;
			XNextEvent(pixelSurface->xDisplay, &e);
			std::cout << "event" << std::endl;
			switch (e.type)
			{
				case 2:
		
					std::cout << "xkey event: " << e.xkey.keycode << std::endl;
					processKeyCode(e.xkey.keycode, shouldStop);

				break;
				case 4:
					std::cout << "xbuttonpress event button=" << e.xbutton.button << std::endl;
					break;	
				case 6:
					std::cout << "xmotion event x=" << e.xmotion.x << " y=" << e.xmotion.y << " xroot=" << e.xmotion.x_root << " yroot=" << e.xmotion.y_root << std::endl;

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
