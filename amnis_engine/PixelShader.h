#pragma once
#include "Graphics.h"
class PixelShader
{
public:
	DECL PixelShader(Graphics* graphics, LPCWSTR pFileName, LPCSTR pEntrypoint = "main", LPCSTR pTarget = "ps_5_0");
	DECL ID3D11PixelShader* get();
	DECL ID3D11PixelShader** getpp();
	DECL LPVOID GetCodeBufferPointer();
	DECL SIZE_T GetCodeBufferSize();
	DECL void setPixelShader(Graphics* graphics);
private:
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderCode;
};

