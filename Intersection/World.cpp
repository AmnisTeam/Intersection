#include "World.h"
#include "Buildings/EnergyOrderer.h"
#include "GameClient.h"
#include "entities/Entity.h"
#include "entities/EntityTree.h"

World::World(RenderWindow* renderWindow, float sizeElementGridX, float sizeElementGridY)
{
	this->renderWindow = renderWindow;
    grid = new Grid(sizeElementGridX, sizeElementGridY);

	registerEntities = new RegisterEntities(this);
	registerBuildings = new RegisterBuildings(this);

	terrain = new Terrain(this);
	gameClient = new GameClient(this);

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

	gameClient->update();
}

void World::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	for (int x = 0; x < buildings.size(); x++)
		if (buildings[x] != nullptr)
		{
			buildings[x]->setPosition({ buildings[x]->getPosX() * grid->sizeElementX, 0, buildings[x]->getPosY() * grid->sizeElementY });
			renderTarget->draw(buildings[x], state);
		}

	for(int x = 0; x < entities.size(); x++)
		if (entities[x] != nullptr)
			renderTarget->draw(entities[x], state);

	renderTarget->draw(terrain, state);
	renderTarget->draw(gameClient, state);
}
