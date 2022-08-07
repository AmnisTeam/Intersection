#include "pch.h"
#include "Texture.h"
#include "Graphics.h"

Texture::Texture(Graphics* graphics, const wchar_t* path)
{
	this->graphics = graphics;
	DirectX::CreateWICTextureFromFile(graphics->device, path, (ID3D11Resource**)&texture, &textureView);
}

void Texture::bind(int slot, bool inPixelShader)
{
	if (inPixelShader)
		graphics->deviceCon->PSSetShaderResources(slot, 1, &textureView);
	else
		graphics->deviceCon->VSSetShaderResources(slot, 1, &textureView);
}
