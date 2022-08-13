#pragma once
#include "Entity.h"
#include "..//ModelsContent.h"

class EntityTree : public Entity
{
public:
	EntityTree(RenderWindow* renderWindow);
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
};

