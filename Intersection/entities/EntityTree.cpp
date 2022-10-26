#include "EntityTree.h"
#include "../World.h"

EntityTree::EntityTree(World* world) : Entity(world, ModelsContent::dragon, 100, 200)
{
	model->setScale({1/20.0f, 1 / 20.0f , 1 / 20.0f });
	setRotation({ 0, PI, 0 });
	getMoveSystem()->moveSpeed = 5;
}

void EntityTree::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	Entity::draw(renderTarget, state);
}

void* EntityTree::clone()
{
	return new EntityTree(world);
}