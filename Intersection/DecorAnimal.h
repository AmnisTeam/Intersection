#pragma once
#include "ObjectInWorld.h"
#include "IDrawable.h"
#include "ModeledObject.h"
#include "MoveSystem.h"
#include "IUpdateable.h"

class World;

class DecorAnimal : public ObjectInWorld, public IDrawable, public IMovable, public IUpdatable {

public:
	ModeledObject* model;
	MoveSystem* moveSystem;
	

	DecorAnimal(World* world, AmnModel* model, float3 spotPosition, float radius);

	

	// Унаследовано через IDrawable
	virtual DECL void draw(RenderTarget* renderTarget, RenderState state) override;

	// Унаследовано через IUpdatable
	virtual void update() override;


protected:
	float radius_ = 1;
	float3 spotPosition_;
	World* world;
private:



	// Унаследовано через IMovable
	virtual MoveSystem* getMoveSystem() override;


};