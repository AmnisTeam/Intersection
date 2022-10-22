#pragma once
#include "Building.h"
#include "../ModelsContent.h"
#include "BoxCollider.h"
class ChaosFurnace : public Building
{
public:
	ChaosFurnace(World* world, int posX, int posY);
	virtual void* clone() override;
};

