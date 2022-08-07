#pragma once
#include <DirectXMath.h>

class RenderWindow;

class RenderState
{
public:
	DirectX::XMMATRIX modelMatrix;
	RenderWindow* renderWindow;
	bool depthStencilOn = true;

	RenderState(RenderWindow* renderWindow);
};