#pragma once
#include <d3d11.h>
#include <WICTextureLoader.h>

class Graphics;

class Texture
{
public:

	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* textureView;

	Graphics* graphics;

	Texture(Graphics* graphics, const wchar_t* path);
	void bind(int slot, bool inPixelShader = true);


};
