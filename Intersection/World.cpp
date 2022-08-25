#include "World.h"
#include "Buildings/EnergyOrderer.h"

World::World(RenderWindow* renderWindow, float sizeElementGridX, float sizeElementGridY)
{
	this->renderWindow = renderWindow;
    grid = new Grid(sizeElementGridX, sizeElementGridY);


	grid->setObstacle(2, 1);
	grid->setObstacle(3, 1);
	grid->setObstacle(3, 2);
	int countGrids;
	grid->findPath({ 1, 2 }, {5, 2}, &countGrids);
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
