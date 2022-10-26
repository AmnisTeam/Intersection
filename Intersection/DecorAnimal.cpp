#include "DecorAnimal.h"
#include "World.h"

DecorAnimal::DecorAnimal(World* world, AmnModel* model, float3 spotPosition, float radius) : ObjectInWorld(world)
{
    this->spotPosition_ = spotPosition;
    this->radius_ = radius;
    this->world = world;
    this->model = new ModeledObject(world->renderWindow, model);
    moveSystem = new MoveSystem(this);
}

void DecorAnimal::draw(RenderTarget* renderTarget, RenderState state)
{
    state.modelMatrix = modelMatrix * state.modelMatrix;
    renderTarget->draw(model, state);
}

void DecorAnimal::update()
{
}

MoveSystem* DecorAnimal::getMoveSystem()
{
    return moveSystem;
}
