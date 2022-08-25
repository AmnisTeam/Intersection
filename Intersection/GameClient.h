#pragma once
#include "IChoosable.h"
#include <vector>
#include "ModeledObject.h"

class World;
class Building;

class GameClient : public IDrawable
{
public:
	World* world;
	std::vector<IChoosable*> choosedObjects;
	int idBuildingsToSet = 1;

	ModeledObject* setPoint;

	GameClient(World* world);
	void addChoosedObject(IChoosable* object);
	void setBuilgingByMouse();
	void update();

	// Унаследовано через IDrawable
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
};

