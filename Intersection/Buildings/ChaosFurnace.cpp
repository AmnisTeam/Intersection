#include "ChaosFurnace.h"
#include "../World.h"
#include "../inventory/skils/SpawnTree.h"

ChaosFurnace::ChaosFurnace(World* world, int posX, int posY) : Building(world, ModelsContent::box, 500, 500, posX, posY, 1, 1)
{
	setOrigin({0, 0, -1});
	model->setTexture(TexturesContent::textureSky, 0);
	//inv->addElement(new SpawnTree(world, this));
}

void* ChaosFurnace::clone()
{
	return new ChaosFurnace(world, posX, posY);
}