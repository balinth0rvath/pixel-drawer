#include "src/pixel_common_headers.h"

class PixelPalette {
public:
	PixelPalette();
	GLfloat getRed(const GLubyte& alpha, const GLubyte& zeta);
	GLfloat getGreen(const GLubyte& alpha, const GLubyte& zeta);
	GLfloat getBlue(const GLubyte& alpha, const GLubyte& zeta);
private:
	std::unique_ptr<std::vector<std::vector<int>>> palette;  

};
