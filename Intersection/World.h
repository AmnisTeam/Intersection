#pragma once
#include "Buildings/grids/Grid.h"
#include "Buildings/Building.h"
#include <vector>
#include "RenderWindow.h"
#include "Terrain.h"
#include "entities/RegisterEntities.h"
#include "Buildings/RegisterBuildings.h"

class GameClient;
class Entity;

class World : public Transformable, public IDrawable
{
public:
	RenderWindow* renderWindow;
	Grid* grid;
	GameClient* gameClient;
	Terrain* terrain;

	RegisterEntities* registerEntities;
	RegisterBuildings* registerBuildings;
	
	std::vector<Building*> buildings;
	std::vector<Entity*> entities;

	World(RenderWindow* renderWindow, float sizeElementGridX, float sizeElementGridY); 

	bool addBuilding(Building* building);
	bool deleteBuilding(Building* building);

	bool addEntity(Entity* entity);
	bool deleteEntity(Entity* entity);

	virtual void update();

	// Унаследовано через IDrawable
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
};

