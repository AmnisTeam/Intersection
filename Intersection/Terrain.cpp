#include "Terrain.h"
#include "World.h"

Terrain::Terrain(World* world)
{
    this->world = world;
    collider = new BoxCollider({ -0.5f, -1, -0.5f }, { 0, 0, 0 }, {15, 1, 15});
    terrain = new ModeledObject(world->renderWindow, ModelsContent::box);
    terrain->setTexture(TexturesContent::stoneWallAlbedo, 0);
    terrain->setTexture(TexturesContent::stoneWallNormalMap, 1);
    terrain->setPosition(collider->getPosition());
    terrain->setOrigin(collider->getOrigin());
    terrain->setRotation(collider->getRotation());
    terrain->setScale(collider->getScale());
}

void Terrain::draw(RenderTarget* renderTarget, RenderState state)
{
    state.modelMatrix = modelMatrix * state.modelMatrix;
    renderTarget->draw(terrain, state);
}

bool Terrain::raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState)
{
    return collider->raycast(ray, hitPoint, colliderState);
}
