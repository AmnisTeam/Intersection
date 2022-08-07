#pragma once
#include "Graphics.h"
class Buffer
{
public:
	Buffer(Graphics* graphics, UINT BindFlags, void* pData, UINT ByteWidth, D3D11_USAGE usage = D3D11_USAGE_DEFAULT, UINT CPUAccessFlags = 0, UINT MiscFlags = 0, UINT StructureByteStride = 0);
	ID3D11Buffer* get();
	ID3D11Buffer** getpp();
private:
	ID3D11Buffer* buffer;
};

