#pragma once
#include "Building.h"
#include "../ModelsContent.h"
#include "BoxCollider.h"
class ChaosFurnace : public Building
{
public:
	BoxCollider* boxCollider;

	ChaosFurnace(World* world, int posX, int posY);
	virtual void* clone() override;
	virtual Collider* getCollider() override;
};

