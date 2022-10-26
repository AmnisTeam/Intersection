#include "GameClient.h"
#include "World.h"
#include "Buildings/Building.h"
#include "entities/EntityTree.h"
#include "entities/commandSystem/commands/CommandMove.h"

GameClient::GameClient(World* world)
{
    this->world = world;
	setPoint = new ModeledObject(world->renderWindow, ModelsContent::box);
	setPoint->setTexture(TexturesContent::textureSky, 0);
	setPoint->setTexture(TexturesContent::flatNormalMap, 1);
}

void GameClient::addChoosedObject(IColliderable* object)
{
	for (int x = 0; x < choosedObjects.size(); x++)
		if (choosedObjects[x] == object)
			return;
	choosedObjects.push_back(object);
}

void GameClient::setBuilgingByMouse()
{
	if (/*world->renderWindow->window->rawMouseLeftButtonDown*/GetAsyncKeyState('R') && idBuildingsToSet != -1)
	{
		Ray ray = world->renderWindow->boundCamera->castRayFromMouse();

		RayHitPoint hitPoint;
		if (world->terrain->raycast(ray, &hitPoint))
		{
			int pX = floor((float)hitPoint.position.x / world->grid->sizeElementX);
			int pZ = floor((float)hitPoint.position.z / world->grid->sizeElementY);

			//pX = hitPoint.position.x < 0 ? pX - 1 : pX;
			//pZ = hitPoint.position.z < 0 ? pZ - 1 : pZ;

			pZ++;

			Building* building = world->registerBuildings->createBuilding(idBuildingsToSet, pX, pZ);
			world->addBuilding(building);
		}
	}
}

void GameClient::moveEntitiesByMouse()
{
	if (world->renderWindow->window->rawMouseRightButtonDown)
	{
		Ray ray = world->renderWindow->boundCamera->castRayFromMouse();
		for (int x = 0; x < choosedObjects.size(); x++)
		{
			Entity* entity = dynamic_cast<Entity*>(choosedObjects[x]);
			if (entity)
			{
				RayHitPoint hitPoint;
				if (world->terrain->raycast(ray, &hitPoint))
				{
					if (!world->renderWindow->window->getKeyState(VK_SHIFT))
						entity->clearCommands();

					float3 entityPosition = entity->getPosition();

					//int startX = (float)entityPosition.x / world->grid->sizeElementX;
					//int startZ = (float)entityPosition.z / world->grid->sizeElementY;

					//startX = hitPoint.position.x < 0 ? startX - 1 : startX;
					//startZ = hitPoint.position.z < 0 ? startZ - 1 : startZ;
					//startZ += 1;


					//int endX = (float)hitPoint.position.x / world->grid->sizeElementX;
					//int endZ = (float)hitPoint.position.z / world->grid->sizeElementY;

					//endX = hitPoint.position.x <= 0 ? endX - 1 : endX;
					//endZ = hitPoint.position.z <= 0 ? endZ - 1 : endZ;

					//endZ++;

					int startX = floor((float)entityPosition.x / world->grid->sizeElementX);
					int startZ = floor((float)entityPosition.z / world->grid->sizeElementY);

					int endX = floor((float)hitPoint.position.x / world->grid->sizeElementX);
					int endZ = floor((float)hitPoint.position.z / world->grid->sizeElementY);
					startZ++;
					endZ++;

					GridElement* gridElement;
					world->grid->getGridElement(endX, endZ, &gridElement);

					if (gridElement != nullptr ? !gridElement->getObstacle() : true)
					{
						entity->addCommand(new CommandMove(hitPoint.position));
						//int countGrids;
						//float3* path = world->grid->findShortestPath(entityPosition, hitPoint.position, &countGrids);

						////int countGrids;
						////int2* path = world->grid->findPath(entityPosition, hitPoint.position, &countGrids);

						//for (int y = 0; y < countGrids; y++)
						//	entity->addMoveTarget({ (float)path[y].x/* * world->grid->sizeElementX + world->grid->sizeElementX / 2*/, 0, (float)path[y].z/* * world->grid->sizeElementY - world->grid->sizeElementY / 2*/ });
					}
				}
			}
		}
	}
}

void GameClient::update()
{
	if (world->renderWindow->window->rawMouseLeftButtonDown)
	{
		bool intersect = false;
		Ray ray = world->renderWindow->boundCamera->castRayFromMouse();
		for (int x = 0; x < world->buildings.size(); x++)
			if (world->buildings[x] != nullptr)
			{
				RayHitPoint hitPoint;
				if (world->buildings[x]->raycast(ray, &hitPoint))
				{
					addChoosedObject(world->buildings[x]);
					if (!intersect)
						intersect = true;
				}
			}

		for (int x = 0; x < world->entities.size(); x++)
			if (world->entities[x] != nullptr)
			{
				IColliderable* choosable = dynamic_cast<IColliderable*>(world->entities[x]);
				RayHitPoint hitPoint;
				if (choosable->raycast(ray, &hitPoint))
				{
					addChoosedObject(choosable);
					if (!intersect)
						intersect = true;
				}
			}

		if(!intersect)
			choosedObjects.clear();
	}

	setBuilgingByMouse();
	moveEntitiesByMouse();
}

void GameClient::draw(RenderTarget* renderTarget, RenderState state)
{
	Ray ray = world->renderWindow->boundCamera->castRayFromMouse();

	RayHitPoint hitPoint;
	if (world->terrain->raycast(ray, &hitPoint))
	{
		int pX = (float)hitPoint.position.x / world->grid->sizeElementX;
		int pZ = (float)hitPoint.position.z / world->grid->sizeElementY;

		pX = hitPoint.position.x <= 0 ? pX - 1 : pX;
		pZ = hitPoint.position.z <= 0 ? pZ - 1 : pZ;

		pZ += 1;

		setPoint->setPosition({pX * world->grid->sizeElementX, 0, pZ * world->grid->sizeElementY});
		setPoint->setScale({ world->registerBuildings->buildings[idBuildingsToSet]->width * world->grid->sizeElementX, 0.5f, world->registerBuildings->buildings[idBuildingsToSet]->height * world->grid->sizeElementY });
		setPoint->setOrigin({0, 0, -1});
		renderTarget->draw(setPoint, state);
	}
}
