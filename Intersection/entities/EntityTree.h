#pragma once
#include "Entity.h"
#include "..//ModelsContent.h"

class World;

class EntityTree : public Entity
{
public:
	EntityTree(World* world);
	virtual void draw(RenderTarget* renderTarget, RenderState state) override;

	// ������������ ����� Entity
	virtual void* clone() override;
};

