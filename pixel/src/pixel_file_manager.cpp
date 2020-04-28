#include "src/pixel_file_manager.h"

void PixelFileManager::loadFile(const int& fileNumber, const std::unique_ptr<PixelRenderer>& pixelRenderer)
{
	std::unique_ptr<std::vector<GLuint>> copyBuffer = std::make_unique<std::vector<GLuint>>(1024, 255);
	pixelRenderer->setColorBuffer(copyBuffer);
}
