#include "pch.h"
#include "InnerTexturesContent.h"
#include "RenderWindow.h"
#include "Texture.h"

Texture* InnerTexturesContent::pureWhite;

void InnerTexturesContent::load(RenderWindow* renderWindow)
{
	std::wstring path;
	unsigned int tex_width = 1;
	unsigned int tex_height = 1;
	unsigned char* pixels = (unsigned char*)calloc(tex_width * tex_height, 1);

	for(int i = 0; i < tex_width * tex_height; i++)
		pixels[i] = 255;

	pureWhite = new Texture(renderWindow->graphics, pixels, tex_width, tex_height, DXGI_FORMAT_R8G8B8A8_UNORM, 1);
}