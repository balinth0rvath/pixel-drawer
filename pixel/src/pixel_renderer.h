#include <memory>
#include "src/pixel_gl_program_manager.h"
#include "src/pixel_surface.h"

class PixelRenderer {
public:
	void render(const std::unique_ptr<PixelGLProgramManager>& pixelGLProgramManager, const std::unique_ptr<PixelSurface>& pixelSurface);
};

