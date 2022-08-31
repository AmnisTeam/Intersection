#include "World.h"
#include "Buildings/EnergyOrderer.h"
#include "GameClient.h"
#include "entities/Entity.h"
#include "entities/EntityTree.h"

World::World(RenderWindow* renderWindow, float sizeElementGridX, float sizeElementGridY)
{
	this->renderWindow = renderWindow;
    grid = new Grid(sizeElementGridX, sizeElementGridY);

	//int2 startPoint = {100, 2};
	//for(int x = startPoint.x - 2; x <= startPoint.x + 2; x++)
	//	for(int y = startPoint.y - 2; y <= startPoint.y + 2; y++)
	//		if(!(x == startPoint.x && y == startPoint.y))
	//			grid->setObstacle(x, y);

	//grid->setObstacle(2, 1);
	//grid->setObstacle(3, 1);
	//grid->setObstacle(3, 2);





	//grid->setObstacle(4, 1);
	//grid->setObstacle(5, 1);
	//grid->setObstacle(6, 1);

	//grid->setObstacle(4, 2);
	//grid->setObstacle(6, 2);

	//grid->setObstacle(4, 3);
	//grid->setObstacle(5, 3);
	//grid->setObstacle(6, 3);

	//int countGrids;
	//int2* path = grid->findPath({1, 2}, { 5, 2 }, &countGrids, 10);
	//
	//for (int x = 0; x < countGrids; x++)
	//{
	//	int2 point = path[x];
	//	int point1 = 0;
	//}


	registerEntities = new RegisterEntities(this);
	registerBuildings = new RegisterBuildings(this);

	terrain = new Terrain(this);
	gameClient = new GameClient(this);
	boxColliderModel = new ModeledObject(renderWindow, ModelsContent::box);
	//EnergyOrderer* e1 = new EnergyOrderer(this, 0, 0);
	//EnergyOrderer* e2 = new EnergyOrderer(this, 5, 0);

	//addBuilding(e1);
	//addBuilding(e2);

	EntityTree* tree = new EntityTree(this);
	tree->setPosition({0, 0, 10});
	addEntity(tree);
}

bool World::addBuilding(Building* building)
{
	if (grid->setBuilding(building))
	{
		for (int x = 0; x < buildings.size(); x++)
			if (buildings[x] == nullptr)
			{
				buildings[x] = building;
				return true;
			}

		buildings.push_back(building);
		return true;
	}
	return false;
}

bool World::deleteBuilding(Building* building)
{
	grid->unsetBuilding(building);
	for (int x = 0; x < buildings.size(); x++)
	{
		if (buildings[x] == building)
		{
			buildings[x] = nullptr;
			delete building;
			return true;
		}
	}
	return false;
}

bool World::addEntity(Entity* entity)
{
	for (int x = 0; x < entities.size(); x++)
	{
		if (entities[x] == nullptr)
		{
			entities[x] = entity;
			return true;
		}
	}
	entities.push_back(entity);
	return true;
}

bool World::deleteEntity(Entity* entity)
{
	for (int x = 0; x < entities.size(); x++)
	{
		if (entities[x] == entity)
		{
			entities[x] = nullptr;
			delete entity;
			return true;
		}
	}
	return false;
}

void World::update()
{
	for (int x = 0; x < entities.size(); x++)
		if (entities[x] != nullptr)
			entities[x]->update();
	gameClient->update();
}

void World::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	for (int x = 0; x < buildings.size(); x++)
		if (buildings[x] != nullptr)
		{
			buildings[x]->setPosition({ buildings[x]->getPosX() * grid->sizeElementX, 0, buildings[x]->getPosY() * grid->sizeElementY });

			boxColliderModel->setPosition(buildings[x]->getPosition());
			boxColliderModel->setScale({ buildings[x]->width * grid->sizeElementX, 1, buildings[x]->height * grid->sizeElementY });
			boxColliderModel->setOrigin({0, 0, -1});
			renderTarget->draw(buildings[x], state);
			renderTarget->draw(boxColliderModel, state);
		}


	for (int x = 0; x < entities.size(); x++)
		if (entities[x] != nullptr)
		{
			boxColliderModel->setPosition(entities[x]->getPosition());
			boxColliderModel->setScale(entities[x]->getScale());
			boxColliderModel->setOrigin(entities[x]->getOrigin());
			renderTarget->draw(boxColliderModel, state);
		}

	for(int x = 0; x < entities.size(); x++)
		if (entities[x] != nullptr)
			renderTarget->draw(entities[x], state);

	renderTarget->draw(terrain, state);
	renderTarget->draw(gameClient, state);
}
