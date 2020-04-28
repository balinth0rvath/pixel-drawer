#include "src/pixel_file_manager.h"

void PixelFileManager::loadFile(const int& fileNumber, const std::unique_ptr<PixelRenderer>& pixelRenderer)
{
	std::unique_ptr<std::vector<GLuint>> copyBuffer = std::make_unique<std::vector<GLuint>>(1024, 255);
	pixelRenderer->setColorBuffer(copyBuffer);
}

void PixelFileManager::saveFile(const int& fileNumber, const std::unique_ptr<PixelRenderer>& pixelRenderer)
{
	auto copyBuffer = std::make_unique<std::vector<GLuint>>();
	pixelRenderer->getColorBuffer(copyBuffer);

	std::ofstream pixelFileStream;
	std::stringstream fileNameStream;
	fileNameStream << "pixel" << fileNumber << ".txt"; 
	pixelFileStream.open(fileNameStream.str());
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
		pixelFileStream << onePixelStream.str() << "  ";
		
	}
	pixelFileStream.close();	
	std::cout << "got it: " << (*copyBuffer).size() << std::endl;
	
}
