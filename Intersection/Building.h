#pragma once
#include <Transformable.h>
#include <IDrawable.h>
#include <ModeledObject.h>
#include <RenderWindow.h>
#include "Inventory.h"

class Building : public Transformable, public IDrawable 
{
public:
	ModeledObject* model;
	Building(RenderWindow* renderWindow, Model* model, int health, int width, int height);
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;

	int getWidth();
	int getHeight();
	float getHealth();
	Inventory* getInv();

	void damage(float value);

private:
	float health;
	int width;
	int height;
	Inventory* inv;
};