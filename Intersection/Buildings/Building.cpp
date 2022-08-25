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

	float3 origin = { 0, 0, -1 };
	float3 position = { posX * world->grid->sizeElementX, 0, posY * world->grid->sizeElementY };
	float3 size = { world->grid->sizeElementX * width, 1, world->grid->sizeElementY * height };

	boxCollider = new BoxCollider(origin, position, size);
}

void Building::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	renderTarget->draw(model, state);
}

void* Building::getObject()
{
	return this;
}


int Building::getWidth() const { return width; };
int Building::getHeight() const { return height; };
int Building::getPosX() const { return posX; };
int Building::getPosY() const { return posY; };
float Building::getHealth() const { return health; }

void Building::setPosition(float3 position)
{
	Transformable::setPosition(position);
	boxCollider->setPosition(position);
}

void Building::setRotation(float3 rotation)
{
	Transformable::setRotation(rotation);
	boxCollider->setRotation(rotation);
}

void Building::setScale(float3 scale)
{
	Transformable::setScale(scale);
	boxCollider->setScale(scale);
}

void Building::setOrigin(float3 origin)
{
	Transformable::setOrigin(origin);
	//boxCollider->setOrigin(origin);
}

Inventory* Building::getInv() const { return inv; }

Collider* Building::getCollider()
{
	return boxCollider;
}

void Building::damage(float value) { health -= value; };
