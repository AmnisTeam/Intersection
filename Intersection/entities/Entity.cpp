#include "Entity.h"

Entity::Entity(RenderWindow* renderWindow, Model* model)
{
	this->model = new ModeledObject(renderWindow, model);
}

void Entity::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	renderTarget->draw(model, state);
}
