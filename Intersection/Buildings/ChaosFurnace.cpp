#include "ChaosFurnace.h"
#include "../World.h"

ChaosFurnace::ChaosFurnace(World* world, int posX, int posY) : Building(world, ModelsContent::sphere, 500, posX, posY, 2, 2)
{
	float3 origin = { 0, 0, 0 };
	float3 position = { posX * world->grid->sizeElementX, 0, posY * world->grid->sizeElementY };
	float3 size = { world->grid->sizeElementX * width, 1, world->grid->sizeElementY * height };
	boxCollider = new BoxCollider(origin, position, size);
}

void* ChaosFurnace::clone()
{
	return new ChaosFurnace(world, posX, posY);
}

Collider* ChaosFurnace::getCollider()
{
	return boxCollider;
}
