#pragma once
#include <Transformable.h>
#include <IDrawable.h>
#include <ModeledObject.h>
#include "../inventory/Inventory.h"
#include "../IClonable.h"
#include "../IUpdateable.h"
#include "BoxCollider.h"
#include "../Healthable.h"

class World;

class Building : public Healthable, public IDrawable, public IClonable, public IColliderable
{
public:
	int id;
	int width;
	int height;
	int posX;
	int posY;
	Inventory* inv;
	ModeledObject* model;
	BoxCollider* boxCollider;
	Building(World* world, AmnModel* model, float health, float mana, int posX, int posY, int width, int height);
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;

	int getWidth() const;
	int getHeight() const;
	int getPosX() const;
	int getPosY() const;
	float getHealth() const;

	Inventory* getInv() const;

	// Унаследовано через IColliderable
	virtual bool raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState = ColliderState()) override;


	// Унаследовано через IUpdatable
	virtual void update() override;


	// Унаследовано через Healthable
	virtual void death() override;


};