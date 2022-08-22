#pragma once
#include "Transformable.h"
#include "mymath.h"
#include "decl.h"
class Collider : public Transformable
{
public:

	Collider();
	DECL virtual bool raycast(float3 rayOrigin, float3 rayDirection, float3* hitPoint) = 0;
};

