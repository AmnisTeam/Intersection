#pragma once
#include "decl.h"
#include "mymath.h"
#include "Ray.h"
#include "ColliderState.h"

struct RayHitPoint
{
	bool intersect;
	float3 position;
	double distance;
	bool needCheckNear = false;
};

class IColliderable
{
public:
	DECL virtual bool raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState = ColliderState()) = 0;
};