#include "Building.h"
#include "../World.h"

Building::Building(World* world, AmnModel* model, float health, float mana, int posX, int posY, int width, int height) : Healthable(world, health, mana)
{
	this->model = new ModeledObject(world->renderWindow, model);
	this->health = health;
	this->width = width;
	this->height = height;
	this->posX = posX;
	this->posY = posY;
	this->inv = new Inventory();

	float3 origin = { 0, 0, -1 };
	float3 position = { posX * world->grid->sizeElementX, 0, posY * world->grid->sizeElementY };
	float3 size = { world->grid->sizeElementX * width, 1, world->grid->sizeElementY * height };

	boxCollider = new BoxCollider(origin, position, size);
}


int Building::getWidth() const { return width; };
int Building::getHeight() const { return height; };
int Building::getPosX() const { return posX; };
int Building::getPosY() const { return posY; };
float Building::getHealth() const { return health; }

Inventory* Building::getInv() const { return inv; }

bool Building::raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState)
{
	return boxCollider->raycast(ray, hitPoint, colliderState);
}

void Building::update()
{
	Healthable::update();
	inv->update();
}

void Building::death()
{
	world->deleteBuilding(this);
}

void Building::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	renderTarget->draw(model, state);
}
