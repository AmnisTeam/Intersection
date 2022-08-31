#include "ChaosFurnace.h"
#include "../World.h"

ChaosFurnace::ChaosFurnace(World* world, int posX, int posY) : Building(world, ModelsContent::sphere, 500, posX, posY, 1, 1)
{

}

void* ChaosFurnace::clone()
{
	return new ChaosFurnace(world, posX, posY);
}