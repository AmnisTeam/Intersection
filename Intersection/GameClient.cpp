#include "GameClient.h"
#include "World.h"
#include "Buildings/Building.h"
#include "entities/EntityTree.h"
#include "entities/commandSystem/commands/CommandMove.h"
#include "entities/commandSystem/commands/CommandMoveTo.h"

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
	if (world->renderWindow->window->mouse.rawMouseRButtonDown)//rawMouseRightButtonDown
	{
		Ray ray = world->renderWindow->boundCamera->castRayFromMouse();
		RayHitPoint hitPoint;
		bool isTerrainCollide = world->terrain->raycast(ray, &hitPoint);
		
		Entity* entityCollide = nullptr;
		RayHitPoint entityHitPoint;
		for (Entity* entity : world->entities)
			if(entity != nullptr)
				if (entity->raycast(ray, &entityHitPoint))
				{
					entityCollide = entity;
					break;
				}

		bool isEntityCollide = entityCollide != nullptr;

		if (isEntityCollide)
		{
			for (int x = 0; x < choosedObjects.size(); x++)
			{
				Entity* entity = dynamic_cast<Entity*>(choosedObjects[x]);
				if(entity != entityCollide)
					entity->addCommand(new CommandMoveTo(entityCollide, 2));
			}
		} 
		else if (isTerrainCollide)
		{
			for (int x = 0; x < choosedObjects.size(); x++)
			{
				Entity* entity = dynamic_cast<Entity*>(choosedObjects[x]);
				if (entity)
				{
					if (!world->renderWindow->window->keyboard.KeyIsPressed(VK_SHIFT))//getKeyState(VK_SHIFT)
						entity->clearCommands();

					float3 entityPosition = entity->getPosition();

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
					}
				}
			}
		}
	}
}

void GameClient::update()
{
	if (world->renderWindow->window->mouse.rawMouseLButtonDown)//rawMouseLeftButtonDown
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
					if (!world->renderWindow->window->keyboard.KeyIsPressed(VK_SHIFT))//getKeyState(VK_SHIFT)
						choosedObjects.clear();
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
