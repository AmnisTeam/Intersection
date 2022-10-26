#include "MeleeEntity.h"

MeleeEntity::MeleeEntity(World* world, AmnModel* model, float health, float mana, float damage) : Entity(world,model, health, mana)
{
	this->damage = damage;
}

void MeleeEntity::attack(Healthable* healthable)
{
}
