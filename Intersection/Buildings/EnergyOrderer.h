#pragma once
#include "Building.h"
#include "../ModelsContent.h"
#include "BoxCollider.h"
class EnergyOrderer : public Building
{
public:

	EnergyOrderer(World* world, int posX, int posY);

	virtual void* clone() override;
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;

};

