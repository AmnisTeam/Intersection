#pragma once
#include "Building.h"
#include "../ModelsContent.h"
class ChaosFurnace : public Building
{
public:
	ChaosFurnace(RenderWindow* renderWindow, int posX, int posY);
	virtual void* clone() override;
};

