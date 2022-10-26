#include "EnergyOrderer.h"
#include "../World.h"

EnergyOrderer::EnergyOrderer(World* world, int posX, int posY) : Building(world, ModelsContent::tree, 1000, 100, posX, posY, 1, 1)
{

}


void* EnergyOrderer::clone()
{
	return new EnergyOrderer(world, posX, posY);
}

void EnergyOrderer::draw(RenderTarget* renderTarget, RenderState state)
{
	Building::draw(renderTarget, state);
}
