#pragma once
#include "mymath.h"
#include "decl.h"
class BoxCollider
{
public:
	float3 origin;
	float3 position;
	float3 size;

	BoxCollider(float3 origin, float3 position, float3 size);
	DECL bool rayIntersection(float3 rayOrigin, float3 rayDirection);
};

