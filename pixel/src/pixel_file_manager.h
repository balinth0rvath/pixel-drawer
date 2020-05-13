#pragma once
#include "src/pixel_common_headers.h"
#include "src/pixel_renderer.h"

class PixelFileManager {
public:
	void loadFile(const int& fileNumber, PixelRenderer* const pixelRenderer);
	void saveFile(const int& fileNumber, PixelRenderer* const pixelRenderer);
private:
	inline std::string createFilename(const int& fileNumber);
};
