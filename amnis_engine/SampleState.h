#pragma once
#include "Graphics.h"
class SampleState
{
public:
	ID3D11SamplerState* sampleState;
	SampleState(Graphics* graphics);
	void set(Graphics* graphics);
};

