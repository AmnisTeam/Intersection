#include "Entity.h"
#include "../World.h"

Entity::Entity(World* world, AmnModel* model)
{
	this->world = world;
	this->model = new ModeledObject(world->renderWindow, model);
	oldPosition = getPosition();
	this->model->setTexture(TexturesContent::flatNormalMap, 1);

	boxCollider = new BoxCollider(getOrigin(), getPosition(), getScale());
	moveSystem_ = new MoveSystem(this);
}

bool Entity::raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState)
{
	return boxCollider->raycast(ray, hitPoint, colliderState);
}

//void Entity::setPositionWithoutSettingOldPosition(float3 position)
//{
//	Transformable::setPosition(position);
//	boxCollider->setPosition(position);
//}

void Entity::goToPosition(float3 position)
{
	moveSystem_->goToPosition(position);
}

void Entity::addMoveTarget(float3 position)
{
	moveSystem_->addMoveTarget(position);
}

void Entity::clearMoveTargets()
{
	moveSystem_->clearMoveTargets();
}

void Entity::updateMovableSystem(double deltaTime)
{
	moveSystem_->updateMovableSystem(deltaTime);
}

int Entity::getMoveTargetsCount()
{
	return moveSystem_->getMoveTargetsCount();
}

void Entity::goToPositionAstar(float3 position)
{
	int nGrids;
	int2* path = world->grid->findPath(getPosition(), position, &nGrids);

	for (int i = 0; i < nGrids; i++)
		addMoveTarget({ (float)path[i].x * world->grid->sizeElementX, 0, (float)path[i].y * world->grid->sizeElementY });
}

void Entity::update()
{
	if(activatedAttackBehavior)
		updateAttackBehavior();

	updateMovableSystem(world->renderWindow->graphics->deltaTime);
	setPosition(getPosition() + moveSystem_->velocity * world->renderWindow->graphics->deltaTime);
}

void Entity::draw(RenderTarget* renderTarget, RenderState state)
{
	update();
	state.modelMatrix = modelMatrix * state.modelMatrix;
	renderTarget->draw(model, state);
}

void Entity::setAttackTarget(Entity* entity)
{
	attackTarget_ = entity;
}

void Entity::activateAttackBehavior(bool state)
{
	activatedAttackBehavior = state;
}

void Entity::updateAttackBehavior()
{
	clearMoveTargets();
	if (attackTarget_)
	{
		clearMoveTargets();
		goToPosition(attackTarget_->getPosition());
	}
}

void Entity::setPosition(float3 position)
{
	Transformable::setPosition(position);
	boxCollider->setPosition(position);
}

void Entity::setRotation(float3 rotation)
{
	Transformable::setRotation(rotation);
	boxCollider->setRotation(rotation);
}

void Entity::setScale(float3 scale)
{
	Transformable::setScale(scale);
	boxCollider->setScale(scale);
}

void Entity::setOrigin(float3 origin)
{
	Transformable::setOrigin(origin);
	//boxCollider->setOrigin(origin);
}