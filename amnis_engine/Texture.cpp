#include "pch.h"
#include "Texture.h"
#include "Graphics.h"

Texture::Texture(Graphics* graphics, const wchar_t* path)
{
	this->graphics = graphics;
	DirectX::CreateWICTextureFromFile(graphics->device, path, (ID3D11Resource**)&texture, &textureView);
}

Texture::Texture(Graphics* graphics, unsigned char* buffer, unsigned int width, unsigned int height, DXGI_FORMAT format, int sizeFormatInBytes)
{
	this->width = width;
	this->height = height;

	this->graphics = graphics;
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = format;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sb = {};
	sb.pSysMem = buffer;
	sb.SysMemPitch = width * sizeFormatInBytes;
	sb.SysMemSlicePitch = width * height * sizeFormatInBytes;

	HRESULT hr = graphics->device->CreateTexture2D(&desc, &sb, &texture);
	if (FAILED(hr)) throw;

	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc = {};
	viewDesc.Format = format;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	viewDesc.Texture2D.MipLevels = 1;

	hr = graphics->device->CreateShaderResourceView(texture, &viewDesc, &textureView);
	if (FAILED(hr)) throw;
}

void Texture::bind(int slot, bool inPixelShader)
{
	if (inPixelShader)
		graphics->deviceCon->PSSetShaderResources(slot, 1, &textureView);
	else
		graphics->deviceCon->VSSetShaderResources(slot, 1, &textureView);
}
