#include "src/pixel_file_manager.h"

std::string PixelFileManager::createFilename(const int& fileNumber)
{
	std::stringstream fileNameStream;
	fileNameStream << "pixel" << fileNumber << ".txt"; 
	return fileNameStream.str();
}

void PixelFileManager::loadFile(const int& fileNumber, PixelRenderer* const pixelRenderer)
{
	std::unique_ptr<std::vector<GLuint>> copyBuffer = std::make_unique<std::vector<GLuint>>(0);
	std::string filename = createFilename(fileNumber);
	std::ifstream pixelFileStream(filename);

	if (!pixelFileStream.is_open())
	{
		std::cout << filename << " not found. Create empty canvas " << std::endl;
		std::unique_ptr<std::vector<GLuint>> copyBuffer = 
			std::make_unique<std::vector<GLuint>>(
				pixelRenderer->getXSize() * pixelRenderer->getYSize(), 
				pixelRenderer->getBackgroundColor());
		pixelRenderer->setColorBuffer(copyBuffer.get());
		return;
	}
	char str[7];	
	while (pixelFileStream.get(str,7))
	{
		GLuint pixel = 0;
		for(int pos = 0; pos < 6; ++pos)
		{
			char ch = str[pos];
			GLuint b = (ch<0x41) ? ch - 0x30 : ch - 0x41 + 0x0a;
			pixel = pixel + (b << (4 * (5 - pos)));	
		}
		copyBuffer->push_back(pixel);
	}	
	
	pixelRenderer->setColorBuffer(copyBuffer.get());
}

void PixelFileManager::saveFile(const int& fileNumber, PixelRenderer* const pixelRenderer)
{
	auto copyBuffer = std::make_unique<std::vector<GLuint>>();
	pixelRenderer->getColorBuffer(copyBuffer.get());

	std::ofstream pixelFileStream;

	pixelFileStream.open(createFilename(fileNumber));
	for(auto pixel : *copyBuffer)
	{
		std::stringstream onePixelStream;
		for(int pos = 0; pos < 6; ++pos)
		{
			GLuint oneColorDigit = (pixel & 0x00f00000) >> 20;
			GLubyte ascii = 
				(oneColorDigit < 0xa) ? 
					(GLubyte)oneColorDigit + 0x30 : (GLubyte)oneColorDigit + 0x41 - 0x0a;
			onePixelStream << (char)ascii;
			pixel = pixel << 4;	
		}
		pixelFileStream << onePixelStream.str();
		
	}
	pixelFileStream.close();	
	
}
