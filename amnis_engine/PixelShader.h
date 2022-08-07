#pragma once
#include "Graphics.h"
class PixelShader
{
public:
	PixelShader(Graphics* graphics, LPCWSTR pFileName, LPCSTR pEntrypoint = "main", LPCSTR pTarget = "ps_5_0");
	ID3D11PixelShader* get();
	ID3D11PixelShader** getpp();
	LPVOID GetCodeBufferPointer();
	SIZE_T GetCodeBufferSize();
	void setPixelShader(Graphics* graphics);
private:
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderCode;
};

