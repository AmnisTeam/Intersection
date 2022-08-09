#pragma once
#include "VertexShader.h"
#include "decl.h"

class VSLightSource : public VertexShader
{
public:
	DECL VSLightSource(Graphics* graphics, LPCWSTR VSLightSourcePath);
};

