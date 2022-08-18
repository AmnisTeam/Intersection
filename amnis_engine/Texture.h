#pragma once
#include <d3d11.h>
#include <WICTextureLoader.h>
#include "decl.h"

class Graphics;

class Texture
{
public:
	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* textureView;
	Graphics* graphics;
	unsigned int width;
	unsigned int height;
	DECL Texture(Graphics* graphics, const wchar_t* path);
	DECL Texture(Graphics* graphics, unsigned char* buffer, unsigned int width, unsigned int height, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UINT, int sizeFormatInBytes = 3);
	DECL void bind(int slot, bool inPixelShader = true);
};
