#pragma once
#include "IChoosable.h"
#include <vector>

class World;
class Building;

class GameClient
{
public:
	World* world;
	std::vector<IChoosable*> choosedObjects;
	int idBuildingsToSet = -1;

	GameClient(World* world);
	void addChoosedObject(IChoosable* object);
	void setBuilgingByMouse();
	void update();
};

