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
	Building(RenderWindow* renderWindow, AmnModel* model, int health, int posX, int posY, int width, int height);
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;

	int getWidth() const;
	int getHeight() const;
	int getPosX() const;
	int getPosY() const;
	float getHealth() const;
	Inventory* getInv() const;

	void damage(float value);

private:
	float health;
	int width;
	int height;
	int posX;
	int posY;
	Inventory* inv;
};