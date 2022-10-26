#pragma once
#include "commandSystem/Commandable.h"
#include <IDrawable.h>
#include <ModeledObject.h>
#include "../TexturesContent.h"
#include "../IClonable.h"
#include "BoxCollider.h"
#include "../MoveSystem.h"

class World;

class Entity : public Commandable, public IMovable, public IDrawable, public IClonable, public IColliderable
{
public:
	friend class MoveSystem;
	ModeledObject* model;
	BoxCollider* boxCollider;
	float3 oldPosition;
	float radiusCollision = 0.3f;
	int id;

	Entity(World* world, AmnModel* model, float health, float mana);
	~Entity();
	virtual void update() override;
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;

	virtual void death() override;

	void setAttackTarget(Entity* entity);
	void collisionWithBuildings();

	// Inherited via Transformable
	virtual void setPosition(float3 position) override;
	virtual void setRotation(float3 rotation) override;
	virtual void setScale(float3 scale) override;
	virtual void setOrigin(float3 origin) override;

	virtual MoveSystem* getMoveSystem() override;

	void goToPositionAstar(float3 position);

	virtual bool raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState = ColliderState()) override;
private:
	MoveSystem* moveSystem_;
	Entity* attackTarget_;
	bool activatedAttackBehavior = false;
	float radiusOfPoint = 0.01f;
	const double maxMoveSpeedToNotLoseVelocity = 900000;

	//void setPositionWithoutSettingOldPosition(float3 position);
};