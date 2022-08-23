#include "EnergyOrderer.h"
#include "../World.h"

EnergyOrderer::EnergyOrderer(World* world, int posX, int posY) : Building(world, ModelsContent::tree, 1000, posX, posY, 2, 2)
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
