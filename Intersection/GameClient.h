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
	std::vector<IColliderable*> choosedObjects;
	int idBuildingsToSet = 1;

	ModeledObject* setPoint;

	GameClient(World* world);
	void addChoosedObject(IColliderable* object);
	void setBuilgingByMouse();
	void moveEntitiesByMouse();
	void update();

	// Унаследовано через IDrawable
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
};

