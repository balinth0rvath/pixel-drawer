#include "src/pixel_palette.h"

PixelPalette::PixelPalette()
{
	std::vector<std::vector<GLuint>> paletteLocal 
		// greyscale
		{{0x000000,0x000000,0x505050,0x505050,0xa0a0a0,0xa0a0a0,0xffffff,0xffffff},
		{0x000000,0x000000,0x505050,0x505050,0xa0a0a0,0xa0a0a0,0xffffff,0xffffff},

		// red
		{0x400000,0x400000,0xa00000,0xa00000,0xf00000,0xf00000,0xffffff,0xffffff},
		{0x000000,0x000000,0x505050,0x505050,0xa0a0a0,0xa0a0a0,0xffffff,0xffffff},

		// blue
		{0x000000,0x000000,0x505050,0x505050,0xa0a0a0,0xa0a0a0,0xffffff,0xffffff},
		{0x000000,0x000000,0x505050,0x505050,0xa0a0a0,0xa0a0a0,0xffffff,0xffffff},

		// yellow
		{0x000000,0x000000,0x505050,0x505050,0xa0a0a0,0xa0a0a0,0xffffff,0xffffff},
		{0x000000,0x000000,0x505050,0x505050,0xa0a0a0,0xa0a0a0,0xffffff,0xffffff},

		// green
		{0x000000,0x000000,0x505050,0x505050,0xa0a0a0,0xa0a0a0,0xffffff,0xffffff},
		{0x000000,0x000000,0x505050,0x505050,0xa0a0a0,0xa0a0a0,0xffffff,0xffffff},

		// purple
		{0x000000,0x000000,0x505050,0x505050,0xa0a0a0,0xa0a0a0,0xffffff,0xffffff},
		{0x000000,0x000000,0x505050,0x505050,0xa0a0a0,0xa0a0a0,0xffffff,0xffffff}};
	this->palette = std::make_unique<std::vector<std::vector<GLuint>>>(paletteLocal);
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
