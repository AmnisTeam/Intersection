#pragma once
#include "Transformable.h"
#include "GridElement.h"
#include "../Building.h"
#include <map>

class Grid
{
public:
	float sizeElementX;
	float sizeElementY;

	std::map<int2, GridElement*> element;
	Grid(float sizeElementX, float sizeElementY);

	bool setBuilding(Building* building);
	void unsetBuilding(Building* building);

	void setObstacle(int x, int y);
	bool unsetObstacle(int x, int y);

	bool getGridElement(int x, int y, GridElement** gridElement);

	GridElement** findPath(int2 point1, int2 point2, int* countGrids);
};

