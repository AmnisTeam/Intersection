#include "World.h"
#include "Buildings/EnergyOrderer.h"
#include "GameClient.h"

World::World(RenderWindow* renderWindow, float sizeElementGridX, float sizeElementGridY)
{
	this->renderWindow = renderWindow;
    grid = new Grid(sizeElementGridX, sizeElementGridY);
	gameClient = new GameClient(this);
}

void World::addBuilding(Building* building)
{
	grid->setBuilding(building);
	for (int x = 0; x < buildings.size(); x++)
		if (buildings[x] == nullptr)
		{
			buildings[x] = building;
			return;
		}

	buildings.push_back(building);
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


void World::start()
{
	EnergyOrderer* e1 = new EnergyOrderer(this, 0, 0);
	EnergyOrderer* e2 = new EnergyOrderer(this, 1, 0);

	addBuilding(e1);
	addBuilding(e2);
}

void World::update()
{
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
}
