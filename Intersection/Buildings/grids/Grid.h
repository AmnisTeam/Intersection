#pragma once
#include "Transformable.h"
#include "GridElement.h"
#include "../Building.h"

class Grid : public Transformable 
{
public:
	int sizeGridX;
	int sizeGridY;
	float sizeElementX;
	float sizeElementY;

	GridElement*** element;
	Grid(int sizeGridX, int sizeGridY, float sizeElementX, float sizeElementY, float3 position);

	bool setBuilding(Building* building);
	void unsetBuilding(Building* building);
};

