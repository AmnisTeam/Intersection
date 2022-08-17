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

void RegisterBuildings::init(RenderWindow* renderWindow)
{
	addBuilding(new EnergyOrderer(renderWindow, 0, 0));
	addBuilding(new ChaosFurnace(renderWindow, 0, 0));
}
