#pragma once
#include "Buildings/grids/Grid.h"
#include "Buildings/Building.h"
#include "Register.h"
#include <vector>
#include "RenderWindow.h"
#include "Terrain.h"

class GameClient;

class World : public Transformable, public IDrawable
{
public:
	RenderWindow* renderWindow;
	Grid* grid;
	std::vector<Building*> buildings;
	GameClient* gameClient;
	Terrain* terrain;

	ModeledObject* boxColliderModel;

	World(RenderWindow* renderWindow, float sizeElementGridX, float sizeElementGridY);

	bool addBuilding(Building* building);
	bool deleteBuilding(Building* building);

	virtual void start();
	virtual void update();

	// Унаследовано через IDrawable
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
};

