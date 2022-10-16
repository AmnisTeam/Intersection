#include "Building.h"
#include "../World.h"

Building::Building(World* world, AmnModel* model, int health, int posX, int posY, int width, int height)
{
	this->model = new ModeledObject(world->renderWindow, model);
	this->world = world;
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

void Building::damage(float value) { health -= value; }

bool Building::raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState)
{
	return boxCollider->raycast(ray, hitPoint, colliderState);
}

void Building::update()
{
	inv->update();
}

void Building::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	renderTarget->draw(model, state);
}
