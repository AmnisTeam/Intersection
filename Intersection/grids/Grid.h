#pragma once
#include "Transformable.h"
#include "GridElement.h"
#include "IBuild.h"

class Grid : public Transformable 
{
public:
	int sizeGridX;
	int sizeGridY;
	float sizeElementX;
	float sizeElementY;

	GridElement*** element;
	Grid(int sizeGridX, int sizeGridY, float sizeElementX, float sizeElementY, float3 position);

	bool setBuild(int pX, int pY, IBuild* build);
	void unsetBuild(int pX, int pY);
};

