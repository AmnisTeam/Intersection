#pragma once
#include "Graphics.h"
#include "decl.h"

class Buffer
{
public:
	DECL Buffer();
	DECL Buffer(Graphics* graphics, UINT BindFlags, void* pData, UINT ByteWidth, D3D11_USAGE usage = D3D11_USAGE_DEFAULT, UINT CPUAccessFlags = 0, UINT MiscFlags = 0, UINT StructureByteStride = 0);
	DECL void init(Graphics* graphics, UINT BindFlags, void* pData, UINT ByteWidth, D3D11_USAGE usage = D3D11_USAGE_DEFAULT, UINT CPUAccessFlags = 0, UINT MiscFlags = 0, UINT StructureByteStride = 0);
	DECL ID3D11Buffer* get();
	DECL ID3D11Buffer** getpp();
protected:
	ID3D11Buffer* buffer;
};

