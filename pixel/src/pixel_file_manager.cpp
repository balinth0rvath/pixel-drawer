#include "src/pixel_file_manager.h"

std::string PixelFileManager::createFilename(const int& fileNumber)
{
	std::stringstream fileNameStream;
	fileNameStream << "pixel" << fileNumber << ".txt"; 
	return fileNameStream.str();
}

void PixelFileManager::loadFile(const int& fileNumber, const std::unique_ptr<PixelRenderer>& pixelRenderer)
{
	std::unique_ptr<std::vector<GLuint>> copyBuffer = std::make_unique<std::vector<GLuint>>(0);
	std::ifstream pixelFileStream(createFilename(fileNumber));

	char str[7];	
	while (pixelFileStream.get(str,7))
	{
		std::cout << str << std::endl;
		GLuint pixel = 0;
		for(int pos = 0; pos < 6; ++pos)
		{
			char ch = str[pos];
			GLuint b = (ch<0x41) ? ch - 0x30 : ch - 0x41 + 0x0a;
			pixel = pixel + (b << (4 * (5 - pos)));	
		}
		copyBuffer->push_back(pixel);
	}	
	pixelRenderer->setColorBuffer(copyBuffer);
}

void PixelFileManager::saveFile(const int& fileNumber, const std::unique_ptr<PixelRenderer>& pixelRenderer)
{
	auto copyBuffer = std::make_unique<std::vector<GLuint>>();
	pixelRenderer->getColorBuffer(copyBuffer);

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
