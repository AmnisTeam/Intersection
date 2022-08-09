#pragma once
#include "Graphics.h"
#include "decl.h"

class VertexShader
{
public:
	DECL VertexShader(Graphics* graphics, LPCWSTR pFileName, LPCSTR pEntrypoint = "main", LPCSTR pTarget = "vs_5_0");
	DECL VertexShader(Graphics* graphics, LPCWSTR pFileName, D3D11_INPUT_ELEMENT_DESC* elementDesc, int elementsCount, LPCSTR pEntrypoint = "main", LPCSTR pTarget = "vs_5_0");
	DECL ID3D11VertexShader* get();
	DECL ID3D11VertexShader** getpp();
	DECL ID3D11InputLayout* getLayoutp();
	DECL ID3D11InputLayout** getLayoutpp();
	DECL LPVOID GetCodeBufferPointer();
	DECL SIZE_T GetCodeBufferSize();
	DECL void setVertexShader(Graphics* graphics);
	DECL void setLayout(Graphics* graphics);
	DECL void setVertexShaderAndLayout(Graphics* graphics);
protected:
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderCode;
	ID3D11InputLayout* inputLayout;
};

