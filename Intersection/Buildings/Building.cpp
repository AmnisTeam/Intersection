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
float Building::getHealth() const { return health; };
Inventory* Building::getInv() const { return inv; };

void Building::damage(float value) { health -= value; };
