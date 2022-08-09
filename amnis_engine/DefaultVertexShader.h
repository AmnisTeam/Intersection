#pragma once
#include "VertexShader.h"
#include "decl.h"

class DefaultVertexShader : public VertexShader
{
public:
	DECL DefaultVertexShader(Graphics* graphics, LPCWSTR shaderPath);
};

