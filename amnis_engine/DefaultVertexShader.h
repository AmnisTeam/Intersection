#pragma once
#include "VertexShader.h"

class DefaultVertexShader : public VertexShader
{
public:
	DefaultVertexShader(Graphics* graphics, LPCWSTR shaderPath);
};

