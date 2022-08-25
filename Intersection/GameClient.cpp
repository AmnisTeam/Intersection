#include "GameClient.h"
#include "World.h"
#include "Buildings/Building.h"

GameClient::GameClient(World* world)
{
    this->world = world;
	setPoint = new ModeledObject(world->renderWindow, ModelsContent::box);
	setPoint->setTexture(TexturesContent::textureSky, 0);
	setPoint->setTexture(TexturesContent::flatNormalMap, 1);
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
		Ray ray = world->renderWindow->boundCamera->castRayFromMouse();

		RayHitPoint hitPoint;
		if (world->terrain->raycast(ray, &hitPoint))
		{
			int pX = (float)hitPoint.position.x / world->grid->sizeElementX;
			int pZ = (float)hitPoint.position.z / world->grid->sizeElementY + 1;

			pX = hitPoint.position.x < 0 ? pX - 1 : pX;
			pZ = hitPoint.position.z < 0 ? pZ - 1 : pZ;

			Building* building = RegisterBuildings::createBuilding(idBuildingsToSet, pX, pZ);
			world->addBuilding(building);
		}
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

	setBuilgingByMouse();
}

void GameClient::draw(RenderTarget* renderTarget, RenderState state)
{
	Ray ray = world->renderWindow->boundCamera->castRayFromMouse();

	RayHitPoint hitPoint;
	if (world->terrain->raycast(ray, &hitPoint))
	{
		int pX = (float)hitPoint.position.x / world->grid->sizeElementX;
		int pZ = (float)hitPoint.position.z / world->grid->sizeElementY + 1;

		pX = hitPoint.position.x < 0 ? pX - 1 : pX;
		pZ = hitPoint.position.z < 0 ? pZ - 1 : pZ;

		setPoint->setPosition({pX * world->grid->sizeElementX, 0, pZ * world->grid->sizeElementY});
		setPoint->setScale({ RegisterBuildings::buildings[idBuildingsToSet]->width * world->grid->sizeElementX, 0.5f, RegisterBuildings::buildings[idBuildingsToSet]->height * world->grid->sizeElementY });
		setPoint->setOrigin({0, 0, -1});
		renderTarget->draw(setPoint, state);
	}
}
