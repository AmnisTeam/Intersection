#include "EnergyOrderer.h"

EnergyOrderer::EnergyOrderer(World* world, int posX, int posY) : Building(world, ModelsContent::tree, 1000, posX, posY, 5, 5)
{
	float3 origin = {0, 0, 0};
	float3 position = getPosition();
	float3 size = { width, 1, height };
	boxCollider = new BoxCollider(origin, position, size);
}


void* EnergyOrderer::clone()
{
	return new EnergyOrderer(world, posX, posY);
}

Collider* EnergyOrderer::getCollider()
{
	float3 position = getPosition();
	boxCollider->setPosition(position);
	return boxCollider;
}
