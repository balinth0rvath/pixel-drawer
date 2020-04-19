#include "src/pixel_common_headers.h"
#include "src/pixel_renderer.h"

class PixelController {
public:
	PixelController(std::unique_ptr<PixelRenderer>& pixelRenderer,
					std::unique_ptr<PixelSurface>& pixelSurface,
					std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager);

	void eventLoop();
private:
	const std::unique_ptr<PixelRenderer>& pixelRenderer;
	const std::unique_ptr<PixelSurface>& pixelSurface;
	const std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager;

};
