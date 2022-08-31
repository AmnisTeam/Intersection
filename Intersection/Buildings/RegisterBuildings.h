#pragma once
#include "EnergyOrderer.h"
#include "ChaosFurnace.h"
#include <vector>
class RegisterBuildings
{
public:
	static std::vector<Building*> buildings;

	static void addBuilding(Building* building);
	static Building* createBuilding(int id, int posX, int posY);

	static void init(World* world);
};

