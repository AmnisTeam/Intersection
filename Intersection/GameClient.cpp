#include "GameClient.h"
#include "World.h"

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

void GameClient::update()
{
	if (world->renderWindow->window->rawMouseLeftButtonDown)
	{
		Ray ray = world->renderWindow->boundCamera->castRayFromMouse();
		for (int x = 0; x < world->buildings.size(); x++)
			if (world->buildings[x] != nullptr)
			{
				IChoosable* choosable = dynamic_cast<IChoosable*>(world->buildings[x]);
				float3 hitPoint;
				if (choosable->getCollider()->raycast(ray, &hitPoint))
					addChoosedObject(choosable);
			}
	}
}
