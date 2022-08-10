#include "Building.h"

Building::Building(RenderWindow* renderWindow, Model* model, int health, int width, int height)
{
	this->model = new ModeledObject(renderWindow, model);
	this->health = health;
	this->width = width;
	this->height = height;
}

void Building::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	renderTarget->draw(model, state);
}


int Building::getWidth() { return width; };
int Building::getHeight() { return height; };
float Building::getHealth() { return health; };
Inventory* Building::getInv() { return inv; };

void Building::damage(float value) { health -= value; };
