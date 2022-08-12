#pragma once
#include <DirectXMath.h>
#include "decl.h"
class RenderWindow;

class RenderState
{
public:
	DirectX::XMMATRIX modelMatrix;
	RenderWindow* renderWindow;
	bool depthStencilOn = true;
	bool viewMatrixOn = true;
	bool projectionMatrixOn = true;

	DECL RenderState(RenderWindow* renderWindow);
};