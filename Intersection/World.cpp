#include "World.h"
#include "Buildings/EnergyOrderer.h"
#include "GameClient.h"

World::World(RenderWindow* renderWindow, float sizeElementGridX, float sizeElementGridY)
{
	this->renderWindow = renderWindow;
    grid = new Grid(sizeElementGridX, sizeElementGridY);
}

bool World::addBuilding(Building* building)
{
	if (grid->setBuilding(building))
	{
		for (int x = 0; x < buildings.size(); x++)
			if (buildings[x] == nullptr)
			{
				buildings[x] = building;
				return true;
			}

		buildings.push_back(building);
		return true;
	}
	return false;
}

bool World::deleteBuilding(Building* building)
{
	grid->unsetBuilding(building);
	for (int x = 0; x < buildings.size(); x++)
	{
		if (buildings[x] == building)
		{
			buildings[x] = nullptr;
			delete building;
			return true;
		}
	}
	return false;
}


void World::start()
{
	terrain = new Terrain(this);
	gameClient = new GameClient(this);
	boxColliderModel = new ModeledObject(renderWindow, ModelsContent::box);
	EnergyOrderer* e1 = new EnergyOrderer(this, 0, 0);
	EnergyOrderer* e2 = new EnergyOrderer(this, 5, 0);

	addBuilding(e1);
	addBuilding(e2);
}

void World::update()
{
	gameClient->update();
}

void World::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	for (int x = 0; x < buildings.size(); x++)
		if (buildings[x] != nullptr)
		{
			buildings[x]->setPosition({ buildings[x]->getPosX() * grid->sizeElementX, 0, buildings[x]->getPosY() * grid->sizeElementY });
			IChoosable* choosable= dynamic_cast<IChoosable*>(buildings[x]);
			BoxCollider* collider = dynamic_cast<BoxCollider*>(choosable->getCollider());

			boxColliderModel->setPosition(collider->getPosition());
			boxColliderModel->setScale(collider->getScale());
			boxColliderModel->setOrigin(collider->getOrigin());
			renderTarget->draw(buildings[x], state);
			renderTarget->draw(boxColliderModel, state);
		}
	renderTarget->draw(terrain, state);
	renderTarget->draw(gameClient, state);
}
