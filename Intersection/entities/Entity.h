#pragma once
#include <Transformable.h>
#include <IDrawable.h>
#include <ModeledObject.h>
#include "../TexturesContent.h"
#include "../IClonable.h"
#include "BoxCollider.h"
#include "../MoveSystem.h"
#include "../HealthSystem.h"

class World;

class Entity : public Transformable, public IMovable, public IDrawable, public IClonable, public IColliderable, public IHealthable
{
public:
	friend class MoveSystem;
	ModeledObject* model;
	World* world;
	BoxCollider* boxCollider;
	int id;
	Entity(World* world, AmnModel* model);
	virtual void update();
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;

	void setAttackTarget(Entity* entity);
	void activateAttackBehavior(bool state);
	void updateAttackBehavior();

	// Inherited via Transformable
	virtual void setPosition(float3 position) override;
	virtual void setRotation(float3 rotation) override;
	virtual void setScale(float3 scale) override;
	virtual void setOrigin(float3 origin) override;

	// Inherited via IMovable
	virtual void goToPosition(float3 position) override;
	virtual void addMoveTarget(float3 position) override;
	virtual void clearMoveTargets() override;
	virtual void rotateViewDirectionTo(float3 dir) override;
	virtual void updateMovableSystem(double deltaTime) override;

	// Inherited via IHealthable
	virtual void OnDeath();

	void goToPositionAstar(float3 position);

	virtual bool raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState = ColliderState()) override;
private:
	MoveSystem* moveSystem_;
	Entity* attackTarget_;
	bool activatedAttackBehavior = false;
	float radiusOfPoint = 0.01f;
	const double maxMoveSpeedToNotLoseVelocity = 900000;
	float3 oldPosition;
	
	// AttackSystem
	float entityRadius = 1;
};