#pragma once
#include "VertexShader.h"

class VSLightSource : public VertexShader
{
public:
	VSLightSource(Graphics* graphics, LPCWSTR VSLightSourcePath);
};

