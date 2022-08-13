#pragma once
#include "../Building.h"
class GridElement
{
public:
	GridElement();

	void setBuilding(Building* building);
	void setObstacle(bool haveObstacle);

	void* getBuilding() const;
	bool getObstacle() const;
private:
	Building* building = nullptr;
	bool haveObstacle = false;

};

