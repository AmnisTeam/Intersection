#include "GameClient.h"
#include "World.h"
#include "Buildings/Building.h"

GameClient::GameClient(World* world)
{
    this->world = world;
}

void GameClient::addChoosedObject(IChoosable* object)
{
	for (int x = 0; x < choosedObjects.size(); x++)
		if (choosedObjects[x] == object)
			return;
	choosedObjects.push_back(object);
}

void GameClient::setBuilgingByMouse()
{
	if (world->renderWindow->window->rawMouseLeftButtonDown && idBuildingsToSet != -1)
	{
		//Building* building = RegisterBuildings::createBuilding(idBuildingsToSet, );
		//world->addBuilding();
	}
}

void GameClient::update()
{
	if (world->renderWindow->window->rawMouseLeftButtonDown)
	{
		choosedObjects.clear();
		Ray ray = world->renderWindow->boundCamera->castRayFromMouse();
		for (int x = 0; x < world->buildings.size(); x++)
			if (world->buildings[x] != nullptr)
			{
				IChoosable* choosable = dynamic_cast<IChoosable*>(world->buildings[x]);
				RayHitPoint hitPoint;
				if (choosable->getCollider()->raycast(ray, &hitPoint))
					addChoosedObject(choosable);
			}
	}
}
