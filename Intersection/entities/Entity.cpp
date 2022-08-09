#include "Entity.h"

Entity::Entity(RenderWindow* renderWindow, Model* model)
{
	this->model = new ModeledObject(renderWindow, model);
	this->model->setTexture(renderWindow->graphics->texturesContent->flatNormalMap, 1);
}

void Entity::goToPosition(float3 position)
{

}

void Entity::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	renderTarget->draw(model, state);
}
