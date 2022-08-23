#pragma once
#include "Transformable.h"
#include "mymath.h"
#include "decl.h"
#include "Ray.h"
class Collider : public Transformable
{
public:

	Collider();
	DECL virtual bool raycast(Ray ray, float3* hitPoint) = 0;
};

