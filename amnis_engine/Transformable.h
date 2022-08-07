#pragma once
#include "mymath.h"
#include "DirectXMath.h"

class Transformable
{
public:
	DirectX::XMMATRIX modelMatrix = DirectX::XMMatrixIdentity();

	virtual void setPosition(float3 position);
	virtual void setRotation(float3 rotation);
	virtual void setScale(float3 scale);

	float3 getPosition() const;
	float3 getRotation() const;
	float3 getScale() const;

private:
	float3 position = {};
	float3 rotation = {};
	float3 scale = { 1, 1, 1 };

	void updateModelMatrix();
};
