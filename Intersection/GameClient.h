#pragma once
#include "IChoosable.h"
#include <vector>

class World;

class GameClient
{
public:
	std::vector<IChoosable*> choosedObjects;
	World* world;

	GameClient(World* world);
	void addChoosedObject(IChoosable* object);
	void update();
};

