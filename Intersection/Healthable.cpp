#include "Healthable.h"

Healthable::Healthable(World* world, float health, float mana) : ObjectInWorld(world)
{
	this->health = health;
	this->mana = mana;
}

void Healthable::toDamage(Healthable* healthable)
{
	healthable->health -= damage;
}

bool Healthable::toTakeMana(float mana)
{
	if (this->mana >= mana)
	{
		this->mana -= mana;
		return true;
	}
	return false;
}

void Healthable::update()
{
	if (health <= 0)
	{
		death();
	}
}
