#include "Skill.h"

Skill::Skill(World* world, Transformable* transformable)
{
	this->world = world;
	this->transformable = transformable;
}

void Skill::active()
{
	InventoryElement::active();
}

void Skill::passive()
{

}

void Skill::update()
{
	InventoryElement::update();
	passive();
}
