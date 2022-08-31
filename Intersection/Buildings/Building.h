#pragma once
#include <Transformable.h>
#include <IDrawable.h>
#include <ModeledObject.h>
#include "Inventory.h"
#include "../IClonable.h"
#include "BoxCollider.h"

class World;

class Building : public Transformable, public IDrawable, public IClonable, public IColliderable
{
public:
	int id;
	float health;
	int width;
	int height;
	int posX;
	int posY;
	Inventory* inv;
	ModeledObject* model;
	World* world;
	BoxCollider* boxCollider;
	Building(World* world, AmnModel* model, int health, int posX, int posY, int width, int height);
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;

	int getWidth() const;
	int getHeight() const;
	int getPosX() const;
	int getPosY() const;
	float getHealth() const;

	Inventory* getInv() const;

	void damage(float value);

	// ������������ ����� IColliderable
	virtual bool raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState = ColliderState()) override;

};