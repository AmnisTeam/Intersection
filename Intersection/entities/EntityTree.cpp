#include "EntityTree.h"
#include "../World.h"

EntityTree::EntityTree(World* world) : Entity(world, ModelsContent::dragon)
{
	model->setScale({1/20.0f, 1 / 20.0f , 1 / 20.0f });
	setRotation({ 0, PI, 0 });
}

void EntityTree::draw(RenderTarget* renderTarget, RenderState state)
{
	Entity::draw(renderTarget, state);
}

void* EntityTree::clone()
{
	return new EntityTree(world);
}