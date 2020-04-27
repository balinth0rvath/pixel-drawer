#include "src/pixel_palette.h"

PixelPalette::PixelPalette()
{
	std::vector<std::vector<GLuint>> paletteLocal 
		// greyscale 
		{{0x202020,0x202020,0x404040,0x606060,0x808080,0xa0a0a0,0xc0c0c0,0xffffff},
		// brown 
		{0x202020,0x493024,0x634732,0x7c5840,0x856347,0x997450,0xc1976f,0xffffff},
		// green 1 
		{0x202020,0x0f663d,0x287f55,0x409a6f,0x61b58e,0x76c9a1,0x9eedc6,0xffffff},
		// green 2
		{0x202020,0x42b053,0x53bc64,0x66c778,0x7bd289,0x88e197,0xb2efbd,0xffffff},
		// cyan
		{0x202020,0x1aa999,0x29b2a8,0x40bfb8,0x56cdc3,0x73d9ce,0x9dede4,0xffffff},
		// blue 1
		{0x202020,0x2ea9dd,0x45b3db,0x60c0e4,0x79cbe9,0x91d5f2,0xbbe6f3,0xffffff},
		// blue 2
		{0x202020,0x31388e,0x454ca1,0x585eb1,0x6d74c4,0x8389d1,0x9fa7ef,0xffffff},
 		// purple 
		{0x202020,0x43186f,0x5a2f85,0x71499c,0x8c64b3,0xa783cd,0xccaeee,0xffffff},
		// pink 
		{0x202020,0xd03d99,0xd555a5,0xdf6cb3,0xe385c1,0xe99ecf,0xf4c1e1,0xffffff},
		// red 
		{0x202020,0xbd2334,0xc63a4a,0xd1505f,0xd66b77,0xe4848f,0xf4a5b3,0xffffff},
		// orange 
		{0x202020,0xef5932,0xf36b30,0xf67d30,0xf99530,0xf9a633,0xffc238,0xffffff},
		// yellow
		{0x000000,0xffc238,0xffca39,0xfdd33b,0xffdb3c,0xffe33d,0xfeee3f,0xffffff}};
	this->palette = std::make_unique<std::vector<std::vector<GLuint>>>(paletteLocal);
}

GLuint PixelPalette::getColor(const GLubyte& zeta, const GLubyte& alpha)
{
	return (*this->palette)[zeta][alpha];
}

GLubyte PixelPalette::convertZeta(const GLubyte& zeta)
{
	return (zeta < 4) ? 4 - zeta : zeta;
}

GLfloat PixelPalette::getRed(const GLubyte& alpha, const GLubyte& zeta) 
{
	return ((GLfloat)((*this->palette)[alpha][convertZeta(zeta)] >> 16)/ 255.0f);
}

GLfloat PixelPalette::getGreen(const GLubyte& alpha, const GLubyte& zeta) 
{
	return ((GLfloat)(( 0x00ffff & (*this->palette)[alpha][convertZeta(zeta)]) >> 8)/ 255.0f);
}

GLfloat PixelPalette::getBlue(const GLubyte& alpha, const GLubyte& zeta)
{
	return ((GLfloat)(( 0x0000ff & (*this->palette)[alpha][convertZeta(zeta)]))/ 255.0f);
}

GLfloat PixelPalette::getRed(const GLuint& color)
{
	GLuint tmp = color >> 16;
	uint8_t red = (uint8_t) tmp;
	return (GLfloat)red / 0xff;
}

GLfloat PixelPalette::getGreen(const GLuint& color)
{
	GLuint tmp = (color >> 8) & 0xff;
	uint8_t green = (uint8_t) tmp;
	return (GLfloat)green / 0xff;
}

GLfloat PixelPalette::getBlue(const GLuint& color)
{
	uint8_t blue = (uint8_t) (color & 0xff);
	return (GLfloat)blue / 0xff;
}
