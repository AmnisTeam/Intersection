#pragma once
#include "Buildings/grids/Grid.h"
#include "Buildings/Building.h"
#include "Register.h"
#include <vector>
class World : public Transformable, public IDrawable
{
public:
	RenderWindow* renderWindow;
	Grid* grid;
	std::vector<Building*> buildings;

	World(RenderWindow* renderWindow, int sizeGridX, int sizeGridY, float sizeElementGridX, float sizeElementGridY);

	void addBuilding(Building* building);
	bool deleteBuilding(Building* building);

	// Унаследовано через IDrawable
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
};

