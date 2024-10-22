#pragma once
#include "../Building.h"
class GridElement
{
public:
	GridElement();

	static bool isWall(GridElement* gridElement);

	void setBuilding(Building* building);
	void setObstacle(bool haveObstacle);

	Building* getBuilding() const;
	bool getObstacle() const;
private:
	Building* building = nullptr;
	bool haveObstacle = false;

};

