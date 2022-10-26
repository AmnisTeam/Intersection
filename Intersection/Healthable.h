#pragma once
#include "ObjectInWorld.h"
#include "IUpdateable.h"

class Healthable : public ObjectInWorld, public IUpdatable
{
public:
	float health;
	float mana;
	float damage;

	Healthable(World* world, float health, float mana);
	void toDamage(Healthable* healthable);
	virtual void death() = 0;
	bool toTakeMana(float mana);

	virtual void update() override;
};

