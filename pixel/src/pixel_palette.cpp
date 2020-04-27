#include "src/pixel_palette.h"

PixelPalette::PixelPalette()
{
	std::vector<std::vector<GLuint>> paletteLocal 
		// greyscale 00
		{{0x000000,0x202020,0x404040,0x606060,0x808080,0xa0a0a0,0xc0c0c0,0xffffff},
		{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

		// red 02
		{0x000000,0x200000,0x400000,0x600000,0x800000,0xa00000,0xc00000,0xff0000},
		{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

		// green 04
		{0x000000,0x002000,0x004000,0x006000,0x008000,0x00a000,0x00c000,0x00ff00},
		{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

		// yellow 06
		{0x000000,0x902020,0xa0533d,0xcd853f,0xa0a0a0,0xa0a000,0xc0c000,0xffff00},
		{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

		// blue 08
		{0x000000,0x000020,0x000040,0x000060,0x000080,0x0000a0,0x0000c0,0x0000ff},
		{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000},

		// purple 10
		{0x000000,0x400040,0x800080,0xa000a0,0x05a0a0,0x10c0c0,0x53f0f0,0xffffff},
		{0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000,0x000000}};
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
