#include "EntityTree.h"

EntityTree::EntityTree(RenderWindow* renderWindow) : Entity(renderWindow, ModelsContent::tree)
{
}

void EntityTree::draw(RenderTarget* renderTarget, RenderState state)
{
	Entity::draw(renderTarget, state);
}
