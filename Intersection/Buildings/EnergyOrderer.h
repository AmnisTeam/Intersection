#pragma once
#include "Building.h"
#include "../ModelsContent.h"
class EnergyOrderer : public Building
{
public:
	EnergyOrderer(RenderWindow* renderWindow, int posX, int posY);
	virtual void* clone() override;
};

