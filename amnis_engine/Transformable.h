#pragma once
#include "mymath.h"
#include <DirectXMath.h>
#include "decl.h"

class Transformable
{
public:
	DirectX::XMMATRIX modelMatrix = DirectX::XMMatrixIdentity();

	DECL virtual void setPosition(float3 position);
	DECL virtual void setRotation(float3 rotation);
	DECL virtual void setScale(float3 scale);
	DECL virtual void setOrigin(float3 origin);

	DECL float3 getPosition() const;
	DECL float3 getRotation() const;
	DECL float3 getScale() const;
	DECL float3 getOrigin() const;

private:
	float3 position = {};
	float3 rotation = {};
	float3 origin = {};
	float3 scale = { 1, 1, 1 };

	DECL void updateModelMatrix();
};
