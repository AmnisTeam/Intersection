#include "DecorAnimal.h"
#include "World.h"

DecorAnimal::DecorAnimal(World* world, AmnModel* model, float3 spotPosition, float radius)
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

void DecorAnimal::goToPosition(float3 position)
{
    moveSystem->goToPosition(position);
}

void DecorAnimal::addMoveTarget(float3 position)
{
    moveSystem->addMoveTarget(position);
}

void DecorAnimal::clearMoveTargets()
{
    moveSystem->clearMoveTargets();
}

void DecorAnimal::rotateViewDirectionTo(float3 dir)
{
    moveSystem->rotateViewDirectionTo(dir);
}

void DecorAnimal::updateMovableSystem(double deltaTime)
{
    moveSystem->updateMovableSystem(deltaTime);
}

void DecorAnimal::update()
{
    updateMovableSystem(world->renderWindow->graphics->deltaTime);
}

int DecorAnimal::getMoveTargetsCount()
{
    return moveSystem->getMoveTargetsCount();
}
