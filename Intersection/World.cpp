#include "World.h"
#include "Buildings/EnergyOrderer.h"
#include "GameClient.h"
#include "entities/Entity.h"
#include "entities/EntityTree.h"

World::World(RenderWindow* renderWindow, float sizeElementGridX, float sizeElementGridY)
{
	this->renderWindow = renderWindow;
    grid = new Grid(sizeElementGridX, sizeElementGridY);
	decorAnimalBug1 = new DecorAnimalBug(this, float3{ 3,0,3 }, 3);
	decorAnimalBug2 = new DecorAnimalBug(this, float3{ -3,0,-3 }, 3);


	registerEntities = new RegisterEntities(this);
	registerBuildings = new RegisterBuildings(this);

	terrain = new Terrain(this);
	gameClient = new GameClient(this);

	//grid->setObstacle(0, 3);
	//grid->setObstacle(0, 2);
	//grid->setObstacle(0, 1);
	//grid->setObstacle(0, 0);
	//grid->setObstacle(0, -1);

	//int countGrids;
	//float3* path = grid->findShortestPath({ -2, 0, 3 }, {2, 0, -3}, &countGrids);
	//
	//for (int x = 0; x < countGrids; x++)
	//{
	//	float3 p = path[x];
	//	int point = 0;
	//}

	//EnergyOrderer* e1 = new EnergyOrderer(this, 0, 0);
	//EnergyOrderer* e2 = new EnergyOrderer(this, 5, 0);
	//addBuilding(e1);
	//addBuilding(e2);
	//EntityTree* tree = new EntityTree(this);
	//tree->setPosition({1, 0, 2});
	//addEntity(tree);

	//EntityTree* leftEntity = new EntityTree(this);
	//EntityTree* rightEntity = new EntityTree(this);

	//leftEntity->setPosition(float3{-5, 0, 0});
	//leftEntity->activateAttackBehavior(true);
	//leftEntity->setAttackTarget(rightEntity);
	//addEntity(leftEntity);

	//rightEntity->setPosition(float3{5, 0, 0});
	//rightEntity->activateAttackBehavior(true);
	//rightEntity->setAttackTarget(leftEntity);
	//addEntity(rightEntity);

	EntityTree* tree = new EntityTree(this);
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
	for (int x = 0; x < buildings.size(); x++)
	{
		if (buildings[x] == building)
		{
			buildingsToDelete.push_back(x);
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
			entityToDelete.push_back(x);
			return true;
		}
	}
	return false;
}

void World::toDelete()
{
	if (!entityToDelete.empty())
		for (auto& x : entityToDelete)
		{
			delete entities[x];
			entities[x] = entities.back();
			entities.pop_back();
		}

	if (!buildingsToDelete.empty())
		for (auto& x : buildingsToDelete)
		{
			grid->unsetBuilding(buildings[x]);
			delete buildings[x];
			buildings[x] = buildings.back();
			buildings.pop_back();
		}
}

void World::update()
{
	for (int x = 0; x < entities.size(); x++)
		if (entities[x] != nullptr)
			entities[x]->update();

	for (auto i : buildings)
		if (i != nullptr)
			i->update();

	decorAnimalBug1->update();
	decorAnimalBug2->update();
	gameClient->update();
}

void World::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	for (int x = 0; x < buildings.size(); x++)
		if (buildings[x] != nullptr)
		{
			buildings[x]->setPosition({ buildings[x]->getPosX() * grid->sizeElementX, 0, buildings[x]->getPosY() * grid->sizeElementY });

		/*	boxColliderModel->setPosition(buildings[x]->getPosition());
			boxColliderModel->setScale({ buildings[x]->width * grid->sizeElementX, 1, buildings[x]->height * grid->sizeElementY });
			boxColliderModel->setOrigin({0, 0, -1});*/
			renderTarget->draw(buildings[x], state);
			//renderTarget->draw(boxColliderModel, state);
		}


	//for (int x = 0; x < entities.size(); x++)
	//	if (entities[x] != nullptr)
	//	{
	//		//boxColliderModel->setPosition(entities[x]->getPosition());
	//		//boxColliderModel->setScale(entities[x]->getScale());
	//		//boxColliderModel->setOrigin(entities[x]->getOrigin());
	//		//renderTarget->draw(boxColliderModel, state);
	//	}

	for(int x = 0; x < entities.size(); x++)
		if (entities[x] != nullptr)
			renderTarget->draw(entities[x], state);

	renderTarget->draw(decorAnimalBug1, state);
	renderTarget->draw(decorAnimalBug2, state);

	renderTarget->draw(terrain, state);
	renderTarget->draw(gameClient, state);
}
