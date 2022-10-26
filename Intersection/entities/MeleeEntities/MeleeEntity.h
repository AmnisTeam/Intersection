#pragma once
#include "../Entity.h"
#include "../../IAttackable.h"

class MeleeEntity : public Entity, public IAttackable
{
public:

	MeleeEntity(World* world, AmnModel* model, float health, float mana, float damage);

	virtual void attack(Healthable* healthable) override;

};

