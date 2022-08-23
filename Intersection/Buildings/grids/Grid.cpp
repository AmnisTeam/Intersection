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
			if (element.find(getKey(x, y)) != element.end())
			{
				GridElement* gridElement = element[getKey(x, y)];
				haveObstacle = gridElement->getObstacle();
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
				if (element.find(getKey(x, y)) == element.end())
					element[getKey(x, y)] = new GridElement();
				element[getKey(x, y)]->setBuilding(building);
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
			if (element.find(getKey(x, y)) != element.end())
			{
				delete element[getKey(x, y)];
				element.erase(getKey(x, y));
			}
}

void Grid::setObstacle(int x, int y)
{
	bool have = element.find(getKey(x, y)) != element.end();
	GridElement* gridElement = nullptr;
	if (have)
		gridElement = element[getKey(x, y)];
	else
	{
		gridElement = new GridElement();
		element[getKey(x, y)] = gridElement;
	}

	gridElement->setObstacle(true);
}

bool Grid::unsetObstacle(int x, int y)
{
	bool have = element.find(getKey(x, y)) != element.end();
	if (have)
	{
		GridElement* gridElement = element[getKey(x, y)];
		if (gridElement->getBuilding() == nullptr)
		{
			gridElement->setObstacle(false);
			return true;
		}
		else
			return false;
	}
	else
		return true;
}

bool Grid::getGridElement(int x, int y, GridElement** gridElement)
{
	bool have = element.find(getKey(x, y)) != element.end();
	if (have)
		*gridElement = element[getKey(x, y)];
	else
	{
		*gridElement = nullptr;
	}
	return have;
}

std::string Grid::getKey(int x, int y)
{
	return std::to_string(x) + "+" + std::to_string(y);
}

GridElement** Grid::findPath(int2 point1, int2 point2, int* countGrids)
{
	GridElement** g = new GridElement*[3];
	*countGrids = 3;
	return g;
}
