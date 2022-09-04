#include "EntityTree.h"
#include "../World.h"

EntityTree::EntityTree(World* world) : Entity(world, ModelsContent::tree)
{

}

void EntityTree::draw(RenderTarget* renderTarget, RenderState state)
{
	Entity::draw(renderTarget, state);
}

void* EntityTree::clone()
{
	return new EntityTree(world);
}