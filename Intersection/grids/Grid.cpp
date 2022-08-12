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

bool Grid::setBuild(int pX, int pY, IBuild* build)
{
	bool haveObstacle = false;
	for (int x = pX; x < pX + build->getGridSizeX(); x++)
	{
		for (int y = pY; y < pY + build->getGridSizeY(); y++)
		{
			haveObstacle = element[x][y]->getObstacle();
			if (haveObstacle)
				break;
		}
		if (haveObstacle)
			break;
	}

	if(!haveObstacle)
		for(int x = pX; x < pX + build->getGridSizeX(); x++)
			for (int y = pY; y < pY + build->getGridSizeY(); y++)
				element[x][y]->setBuild(build->getBuild());

	return !haveObstacle;
}

void Grid::unsetBuild(int pX, int pY)
{
	int buildPosX = pX;
	int buildPosY = pY;
	void* build = element[buildPosX][buildPosY]->getBuild();

	while (element[buildPosX][buildPosY]->getBuild() == build)
		buildPosX--;
	buildPosX++;

	while (element[buildPosX][buildPosY]->getBuild() == build)
		buildPosY--;
	buildPosY++;
	
	IBuild* iBuild = (IBuild*)build; //Can be an error!
	for (int x = buildPosX; x < buildPosX + iBuild->getGridSizeX(); x++)
		for (int y = buildPosY; y < buildPosY + iBuild->getGridSizeY(); y++)
			element[x][y]->setBuild(nullptr);
}
