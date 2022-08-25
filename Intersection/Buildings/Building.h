#pragma once
#include <Transformable.h>
#include <IDrawable.h>
#include <ModeledObject.h>
#include "Inventory.h"
#include "../IClonable.h"
#include "../IChoosable.h"
#include "BoxCollider.h"

class World;

class Building : public Transformable, public IDrawable, public IClonable, public IChoosable
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
	virtual void* getObject() override;

	int getWidth() const;
	int getHeight() const;
	int getPosX() const;
	int getPosY() const;
	float getHealth() const;

	virtual void setPosition(float3 position);
	virtual void setRotation(float3 rotation);
	virtual void setScale(float3 scale);
	virtual void setOrigin(float3 origin);

	Inventory* getInv() const;
	virtual Collider* getCollider() override;

	void damage(float value);
};