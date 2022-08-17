#include "Grid.h"

Grid::Grid(float sizeElementX, float sizeElementY)
{
	this->sizeElementX = sizeElementX;
	this->sizeElementY = sizeElementY;
}

bool Grid::setBuilding(Building* building)
{
	bool haveObstacle = false;
	for (int x = building->getPosX(); x < building->getPosX() + building->getWidth(); x++)
	{
		for (int y = building->getPosY(); y < building->getPosY() + building->getHeight(); y++)
		{
			if (element.find({x, y}) != element.end())
			{
				haveObstacle = element[{x, y}]->getObstacle();
				if (haveObstacle)
					break;
			}
		}
		if (haveObstacle)
			break;
	}

	if(!haveObstacle)
		for(int x = building->getPosX(); x < building->getPosX() + building->getWidth(); x++)
			for (int y = building->getPosY(); y < building->getPosY() + building->getHeight(); y++)
			{
				if (element.find({x, y}) == element.end())
					element[{x, y}] = new GridElement();
				element[{x, y}]->setBuilding(building);
			}

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
			if (element.find({ x, y }) != element.end())
			{
				delete element[{x, y}];
				element.erase({ x, y });
			}
}
