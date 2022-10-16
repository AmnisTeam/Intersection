#pragma once
#include "Transformable.h"
#include "IDrawable.h"
#include "ModeledObject.h"
#include "MoveSystem.h"
#include "IUpdateable.h"

class World;

class DecorAnimal : public Transformable, public IDrawable, public IMovable, public IUpdatable {

public:
	ModeledObject* model;
	MoveSystem* moveSystem;
	

	DecorAnimal(World* world, AmnModel* model, float3 spotPosition, float radius);

	

	// Унаследовано через IDrawable
	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;

	// Унаследовано через IMovable
	virtual void goToPosition(float3 position) override;

	virtual void addMoveTarget(float3 position) override;

	virtual void clearMoveTargets() override;

	virtual void updateMovableSystem(double deltaTime) override;

	virtual int getMoveTargetsCount() override;

	// Унаследовано через IUpdatable
	virtual void update() override;


protected:
	float radius_ = 1;
	float3 spotPosition_;
	World* world;
private:


};