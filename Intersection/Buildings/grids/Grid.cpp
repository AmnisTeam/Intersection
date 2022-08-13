#include "Grid.h"

Grid::Grid(int sizeGridX, int sizeGridY, float sizeElementX, float sizeElementY, float3 position)
{
	this->sizeGridX = sizeGridX;
	this->sizeGridY = sizeGridY;
	this->sizeElementX = sizeElementX;
	this->sizeElementY = sizeElementY;
	setPosition(position);

	element = new GridElement * *[sizeGridX];
	for (int x = 0; x < sizeGridX; x++)
	{
		element[x] = new GridElement * [sizeGridY];
		for(int y = 0; y < sizeGridY; y++)
			element[x][y] = new GridElement();
	}
}

bool Grid::setBuilding(Building* building)
{
	bool haveObstacle = false;
	for (int x = building->getPosX(); x < building->getPosX() + building->getWidth(); x++)
	{
		for (int y = building->getPosY(); y < building->getPosY() + building->getHeight(); y++)
		{
			haveObstacle = element[x][y]->getObstacle();
			if (haveObstacle)
				break;
		}
		if (haveObstacle)
			break;
	}

	if(!haveObstacle)
		for(int x = building->getPosX(); x < building->getPosX() + building->getWidth(); x++)
			for (int y = building->getPosY(); y < building->getPosY() + building->getHeight(); y++)
				element[x][y]->setBuilding(building);

	return !haveObstacle;
}

void Grid::unsetBuilding(Building* building)
{
	int pX = building->getPosX();
	int pY = building->getPosY();
	
	int width = building->getWidth();
	int height = building->getHeight();

	for(int x = pX; x < pX + width; x++)
		for (int y = pY; y < pY + height; y++)
		{
			element[x][y]->setBuilding(nullptr);
		}
}
