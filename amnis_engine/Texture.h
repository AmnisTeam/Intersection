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
	DECL Texture(Graphics* graphics, const wchar_t* path);
	DECL void bind(int slot, bool inPixelShader = true);
};
