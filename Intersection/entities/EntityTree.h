#pragma once
#include "Entity.h"

class EntityTree : public Entity
{
public:
	EntityTree(RenderWindow* renderWindow);
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;
};

