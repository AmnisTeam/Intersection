#pragma once
#include "EnergyOrderer.h"
#include "ChaosFurnace.h"
#include <vector>
class RegisterBuildings
{
public:
	World* world;
	std::vector<Building*> buildings;

	RegisterBuildings(World* world);

	void addBuilding(Building* building);
	Building* createBuilding(int id, int posX, int posY);

	void init();
};

