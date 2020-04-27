#include "src/pixel_controller.h"

PixelController::PixelController(std::unique_ptr<PixelRenderer>& pixelRenderer,
								std::unique_ptr<PixelSurface>& pixelSurface,
								std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager,
								std::unique_ptr<PixelPalette>& pixelPalette) :
								pixelRenderer(pixelRenderer),
								pixelSurface(pixelSurface),
								pixelGLProgramManager(pixelGLProgramManager),
								pixelPalette(pixelPalette)
						
{

}

void PixelController::processButton(const int& pointerX, 	
									const int& pointerY, 		
									const int& toggle)
{
	pixelRenderer->unfocusPixel(cursorX, cursorY);
	cursorX = pixelRenderer->getXSize() * ((GLfloat)pointerX / (GLfloat)(pixelSurface->windowWidth));
	cursorY = pixelRenderer->getYSize() * ((GLfloat)(pixelSurface->windowHeight - pointerY) / (GLfloat)(pixelSurface->windowHeight));
	pixelRenderer->focusPixel(cursorX, cursorY);

	if (!toggle)
	{
		pixelRenderer->drawPixel(cursorX, cursorY, currentColor);
	
	} else
	{
		pixelRenderer->togglePixel(cursorX, cursorY, currentColor);
	}
}

void PixelController::processKeyCode(const int& keycode, int& shouldStop)
{
	switch (keycode)
	{
		case X11_ESC:
			shouldStop=1;
			break;
		case X11_SPACE:
			if (pixelRenderer->pixelAnimation->getSphereAnimationState() == PixelAnimationState::stoppedFront)
			{
				GLuint zeta = pixelRenderer->getMainColorIndex();
				GLuint alpha = pixelRenderer->getSubColorIndex();
	
				std::cout << "Palette index: " << zeta << std::endl;
				this->currentColor = pixelPalette->getColor(zeta, alpha);

				pixelRenderer->pixelAnimation->pushSphereBack();
			}	 	
			if (pixelRenderer->pixelAnimation->getSphereAnimationState() == PixelAnimationState::stoppedAway)
			{
				pixelRenderer->pixelAnimation->pullSphereFront();
			}
			break;
		case X11_KEY_UP:
			if (pixelRenderer->pixelAnimation->getSphereAnimationState() == PixelAnimationState::stoppedAway)
			{
				if (this->pixelRenderer->getYSize()-1 > cursorY) 
				{ 
					pixelRenderer->unfocusPixel(cursorX,cursorY);
					cursorY+= 1; 
					pixelRenderer->focusPixel(cursorX,cursorY);

				} 
			} else
			{
				pixelRenderer->incAlpha(dRotation);
			}

			break;
		case X11_KEY_DOWN:
			if (pixelRenderer->pixelAnimation->getSphereAnimationState() == PixelAnimationState::stoppedAway)
			{
				if (cursorY != 0)
				{
					pixelRenderer->unfocusPixel(cursorX,cursorY);
					cursorY-= 1;
						pixelRenderer->focusPixel(cursorX,cursorY);

				}
			} else
			{
				pixelRenderer->decAlpha(dRotation);
			}
			break;
		case X11_KEY_LEFT:
			if (pixelRenderer->pixelAnimation->getSphereAnimationState() == PixelAnimationState::stoppedAway)
			{
				if (cursorX != 0)
				{
					pixelRenderer->unfocusPixel(cursorX,cursorY);
					cursorX-= 1;
					pixelRenderer->focusPixel(cursorX,cursorY);
				}
			} else
			{
				pixelRenderer->decZeta(dRotation);
			}
			break;
		case X11_KEY_RIGHT:
			if (pixelRenderer->pixelAnimation->getSphereAnimationState() == PixelAnimationState::stoppedAway)
			{
				if (this->pixelRenderer->getXSize()-1 > cursorX)
				{
					pixelRenderer->unfocusPixel(cursorX,cursorY);
					cursorX+= 1;
					pixelRenderer->focusPixel(cursorX,cursorY);
				}
			} else
			{
				pixelRenderer->incZeta(dRotation);
			}
			break;
		case X11_KEY_1:
			this->currentColor ^= (0xff << 0x10);
		break;
		case X11_KEY_2:
			this->currentColor ^= (0xff << 0x08);
		break;
		case X11_KEY_3:
			this->currentColor ^= (0xff);
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
		
	pixelRenderer->focusPixel(cursorX,cursorY);
	
	for (;!shouldStop;)
	{
		gettimeofday(&startRenderTime, NULL);
		pixelRenderer->render();
		gettimeofday(&endRenderTime, NULL);
		while (XPending(pixelSurface->xDisplay))
		{
			XEvent e;
			XNextEvent(pixelSurface->xDisplay, &e);
			std::cout << "event type: " << e.type << std::endl;
			switch (e.type)
			{
				case 2:
		
					processKeyCode(e.xkey.keycode, shouldStop);

				break;
				case 4:
					this->buttonPressed = 1;
					std::cout << "xbuttonpress event button=" << e.xbutton.button << std::endl;
					processButton(e.xbutton.x, e.xbutton.y, 1);
					break;	
				case 5:
					this->buttonPressed = 0;
					break;	
				case 6:
					std::cout << "xmotion event x=" << e.xmotion.x << " y=" << e.xmotion.y << " xroot=" << e.xmotion.x_root << " yroot=" << e.xmotion.y_root << std::endl;
					if (this->buttonPressed)
					{	
						processButton(e.xmotion.x, e.xmotion.y, 0);
				 	}	
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
