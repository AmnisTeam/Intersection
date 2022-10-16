#pragma once
#include "../../World.h"
#include "../InventoryElement.h"

class Skill : public InventoryElement
{
public:
	World* world;
	Transformable* transformable;

	Skill(World* world, Transformable* transformable);

	virtual void active() override;
	virtual void passive();
	virtual void update() override;

private:

};

