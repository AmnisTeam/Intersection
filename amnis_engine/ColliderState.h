#pragma once
#include "decl.h"
#include <DirectXMath.h>

class ColliderState
{
public:

	DirectX::XMMATRIX state;
	DECL ColliderState();
	DECL ColliderState(DirectX::XMMATRIX state);
};