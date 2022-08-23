#pragma once
#include "Collider.h"
#include <vector>

class CompositeCollider : public Collider
{
public:
	std::vector<Collider*> colliders;
	DECL CompositeCollider();

	DECL void addCollider(Collider* collider);

	DECL virtual void setPosition(float3 position) override;
	DECL virtual void setRotation(float3 rotation) override;
	DECL virtual void setScale(float3 scale) override;
	DECL virtual void setOrigin(float3 origin) override;

	virtual DECL bool raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState = ColliderState()) override;
};

