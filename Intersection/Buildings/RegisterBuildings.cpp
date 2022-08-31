#include "RegisterBuildings.h"

std::vector<Building*> RegisterBuildings::buildings;

void RegisterBuildings::addBuilding(Building* building)
{
	building->id = buildings.size();
	buildings.push_back(building);
}

Building* RegisterBuildings::createBuilding(int id, int posX, int posY)
{
	Building* building = (Building*)buildings[id]->clone();
	building->id = id;
	building->posX = posX;
	building->posY = posY;
	return building;
}

void RegisterBuildings::init(World* world)
{
	addBuilding(new EnergyOrderer(world, 0, 0));
	addBuilding(new ChaosFurnace(world, 0, 0));
}
