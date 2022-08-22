#pragma once
#include "mymath.h"
#include "Collider.h"

class BoxCollider : public Collider
{
public:

	DECL BoxCollider(float3 origin, float3 position, float3 size);
	DECL virtual bool raycast(float3 rayOrigin, float3 rayDirection, float3* hitPoint) override;
};