#pragma once
#include "pixel_common_headers.h"
#include "pixel_surface.h"

class PixelSurfaceX11 : public PixelSurface {
public:
private:

	void initDisplayClient() override;
	void closeDisplayClient() override;
};

