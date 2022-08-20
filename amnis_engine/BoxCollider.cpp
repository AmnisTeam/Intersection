#include "pch.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider(float3 origin, float3 position, float3 size)
{
	this->origin = origin;
	this->position = position;
	this->size = size;
}

bool BoxCollider::rayIntersection(float3 rayOrigin, float3 rayDirection)
{
	return bool();
}
