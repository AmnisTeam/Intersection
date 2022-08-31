#pragma once
#include <Transformable.h>
#include <IDrawable.h>
#include <ModeledObject.h>
#include "../TexturesContent.h"
#include "../IClonable.h"
#include "BoxCollider.h"

class World;

class Entity : public Transformable, public IDrawable, public IClonable, public IColliderable
{
public:
	ModeledObject* model;
	World* world;
	float3 viewDirecton = {0, 0, 1};
	float3 velocity = {};
	BoxCollider* boxCollider;
	int id;
	double moveSpeed = 2;
	double turningSpeed = PI * 0.5;
	std::vector<float3> moveTargets;
	Entity(World* world, AmnModel* model);
	void goToPosition(float3 position);
	void addMoveTarget(float3 position);
	void clearMoveTargets();
	void rotateViewDirectionTo(float3 dir);
	virtual void update();
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;

	virtual void setPosition(float3 position);
	virtual void setRotation(float3 rotation);
	virtual void setScale(float3 scale);
	virtual void setOrigin(float3 origin);

	// Унаследовано через IColliderable
	virtual bool raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState = ColliderState()) override;

private:
	float radiusOfPoint = 0.01f;
	const double maxMoveSpeedToNotLoseVelocity = 900000;
	float3 oldPosition;
	void movementToTargets();
	void movementToTargets2();
	void moveTo(float3 const position);


};