#pragma once
#include "Transformable.h"
#include "IDrawable.h"
#include "ModeledObject.h"
#include "BoxCollider.h"
#include "ModelsContent.h"
#include "TexturesContent.h"

class World;

class Terrain : public Collider, public IDrawable
{
public:

	ModeledObject* terrain;
	BoxCollider* collider;
	World* world;

	Terrain(World* world);

	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
	virtual bool raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState = ColliderState()) override;
};

