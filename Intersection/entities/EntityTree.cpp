#include "EntityTree.h"
#include "../World.h"

EntityTree::EntityTree(World* world) : Entity(world, ModelsContent::dragon)
{
	model->setScale({1/10.0f, 1 / 10.0f , 1 / 10.0f });
}

void EntityTree::draw(RenderTarget* renderTarget, RenderState state)
{
	Entity::draw(renderTarget, state);
}

void* EntityTree::clone()
{
	return new EntityTree(world);
}
