#include "src/pixel_controller.h"

PixelController::PixelController(std::unique_ptr<PixelRenderer>& pixelRenderer,
								std::unique_ptr<PixelSurface>& pixelSurface,
								std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager,
								std::unique_ptr<PixelPalette>& pixelPalette,
								std::unique_ptr<PixelFileManager>& pixelFileManager) :
								pixelRenderer(pixelRenderer),
								pixelSurface(pixelSurface),
								pixelGLProgramManager(pixelGLProgramManager),
								pixelPalette(pixelPalette),
								pixelFileManager(pixelFileManager)
						
{
}

void PixelController::processButton(const int& pointerX, 	
									const int& pointerY, 		
									const int& toggle)
{
	if (pixelRenderer->checkCursorBounds(cursorX, cursorY))
		pixelRenderer->unfocusPixel(cursorX, cursorY);
	cursorX = pixelRenderer->getXSize() * ((GLfloat)pointerX / (GLfloat)(pixelSurface->windowWidth));
	cursorY = pixelRenderer->getYSize() * ((GLfloat)(pixelSurface->windowHeight - pointerY) / (GLfloat)(pixelSurface->windowHeight));
	

	if (!pixelRenderer->checkCursorBounds(cursorX,cursorY))
	{
		return;
	}

	pixelRenderer->focusPixel(cursorX, cursorY);

	if (!toggle)
	{
		pixelRenderer->drawPixel(cursorX, cursorY, currentColor);
	
	} else
	{
		pixelRenderer->togglePixel(cursorX, cursorY, currentColor);
	}
}

void PixelController::processKeyCode(const int& keycode)
{
	switch (keycode)
	{
		case ESC:
			shouldStop=1;
			break;
		case SPACE:
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
		case KEY_UP:
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
		case KEY_DOWN:
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
		case KEY_LEFT:
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
		case KEY_RIGHT:
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
		case KEY_1:
			this->currentFile = 1;
			this->pixelFileManager->loadFile(1, pixelRenderer);	
			break;
		case KEY_2:
			this->currentFile = 2;
			this->pixelFileManager->loadFile(2, pixelRenderer);	
			break;
		case KEY_3:
			this->currentFile = 3;
			this->pixelFileManager->loadFile(3, pixelRenderer);	
			break;
		case KEY_4:
			this->currentFile = 4;
			this->pixelFileManager->loadFile(4, pixelRenderer);	
			break;
		case KEY_5:
			this->currentFile = 5;
			this->pixelFileManager->loadFile(5, pixelRenderer);	
			break;
		case KEY_6:
			this->currentFile = 6;
			this->pixelFileManager->loadFile(6, pixelRenderer);	
			break;
		case KEY_7:
			this->currentFile = 7;
			this->pixelFileManager->loadFile(7, pixelRenderer);	
			break;
		case KEY_8:
			this->currentFile = 8;
			this->pixelFileManager->loadFile(8, pixelRenderer);	
			break;
		case KEY_9:
			this->currentFile = 9;
			this->pixelFileManager->loadFile(9, pixelRenderer);	
			break;
		default:
			break;
	}
}

void PixelController::eventLoop()
{
	struct timeval startRenderTime, endRenderTime;

	uint8_t counter=0;
	uint32_t sumRenderTime=0;
		
	if (pixelRenderer->checkCursorBounds(cursorX,cursorY))
		pixelRenderer->focusPixel(cursorX,cursorY);
	
	this->pixelFileManager->loadFile(this->currentFile, pixelRenderer);	
	for (;!shouldStop;)
	{
		gettimeofday(&startRenderTime, NULL);
		pixelRenderer->render();
		gettimeofday(&endRenderTime, NULL);
#ifndef IMX6
		while (XPending(pixelSurface->display))
		{
			XEvent e;
			XNextEvent(pixelSurface->display, &e);
			switch (e.type)
			{
				case 2:
		
					processKeyCode(e.xkey.keycode);

				break;
				case 4:
					this->buttonPressed = 1;
					processButton(e.xbutton.x, e.xbutton.y, 1);
					break;	
				case 5:
					this->buttonPressed = 0;
					break;	
				case 6:
					if (this->buttonPressed)
					{	
						processButton(e.xmotion.x, e.xmotion.y, 0);
				 	}	
					break;

				default:
					break;
			}
		}
#endif //IMX6	
		counter++;
		uint32_t start = startRenderTime.tv_usec; 	
		uint32_t end = endRenderTime.tv_usec; 	
		if (end > start)
		{
			sumRenderTime+=	(end - start);
		}
		
		if (!counter)
		{
			pixelFileManager->saveFile(currentFile,pixelRenderer);	
			counter=0;
			double fps = 1000000.0f / (double)(sumRenderTime >> 8);
			std::cout << "Render time: " << (sumRenderTime >> 8) << " usec" << " FPS: " << fps << std::endl;
			sumRenderTime = 0;		
		}

	}

}
