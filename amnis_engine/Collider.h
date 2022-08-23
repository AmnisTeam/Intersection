#pragma once
#include "Transformable.h"
#include "mymath.h"
#include "decl.h"
#include "Ray.h"
#include "ColliderState.h"

struct RayHitPoint
{
	bool intersect;
	float3 position;
	double distance;
};

class Collider : public Transformable
{
public:

	Collider();
	DECL virtual bool raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState = ColliderState()) = 0;
};

