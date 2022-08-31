#include "pch.h"
#include "ColliderState.h"
#include "RenderState.h"

ColliderState::ColliderState()
{
	state = DirectX::XMMatrixIdentity();
}

ColliderState::ColliderState(DirectX::XMMATRIX state)
{
	this->state = state;
}
