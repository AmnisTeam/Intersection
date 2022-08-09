#pragma once
#include "Graphics.h"
#include "decl.h"

class SampleState
{
public:
	ID3D11SamplerState* sampleState;
	DECL SampleState(Graphics* graphics);
	DECL void set(Graphics* graphics);
};

