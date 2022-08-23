#pragma once
#include "Building.h"
#include "../ModelsContent.h"
#include "BoxCollider.h"
class EnergyOrderer : public Building
{
public:
	BoxCollider* boxCollider;

	EnergyOrderer(World* world, int posX, int posY);

	virtual void* clone() override;
	virtual Collider* getCollider() override;
};

