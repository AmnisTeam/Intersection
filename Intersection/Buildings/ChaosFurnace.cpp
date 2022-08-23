#include "ChaosFurnace.h"

ChaosFurnace::ChaosFurnace(World* world, int posX, int posY) : Building(world, ModelsContent::sphere, 500, posX, posY, 2, 2)
{
	float3 origin = { 0, 0, 0 };
	float3 position = { posX, 0, posY };
	float3 size = { width, 1, height };
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
