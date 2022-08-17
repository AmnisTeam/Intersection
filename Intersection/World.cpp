#include "World.h"
#include "Buildings/EnergyOrderer.h"

World::World(RenderWindow* renderWindow, int sizeGridX, int sizeGridY, float sizeElementGridX, float sizeElementGridY)
{
	this->renderWindow = renderWindow;
    grid = new Grid(sizeElementGridX, sizeElementGridY);
	int countX = 10;
	int countY = 10;
	EnergyOrderer*** energyOrderer = new EnergyOrderer **[countX];
	for (int x = 0; x < countX; x++)
	{
		energyOrderer[x] = new EnergyOrderer * [countY];
		for (int y = 0; y < countY; y++)
		{
			energyOrderer[x][y] = (EnergyOrderer*)RegisterBuildings::createBuilding(0, x * 2, y * 2);
			addBuilding(energyOrderer[x][y]);
		}
	}

	deleteBuilding(energyOrderer[5][5]);
	deleteBuilding(energyOrderer[6][5]);
	deleteBuilding(energyOrderer[5][6]);
	deleteBuilding(energyOrderer[6][6]);
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
