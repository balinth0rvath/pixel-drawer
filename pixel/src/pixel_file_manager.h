#pragma once
#include "src/pixel_common_headers.h"
#include "src/pixel_renderer.h"

class PixelFileManager {
public:
	void loadFile(const int& fileNumber, const std::unique_ptr<PixelRenderer>& pixelRenderer);
	void saveFile(const int& fileNumber, const std::unique_ptr<PixelRenderer>& pixelRenderer);
};
