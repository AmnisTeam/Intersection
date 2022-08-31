#include "Entity.h"
#include "../World.h"

Entity::Entity(World* world, AmnModel* model)
{
	this->world = world;
	this->model = new ModeledObject(world->renderWindow, model);
	oldPosition = getPosition();
	this->model->setTexture(TexturesContent::flatNormalMap, 1);

	boxCollider = new BoxCollider(getOrigin(), getPosition(), getScale());
}

void Entity::moveTo(float3 const position)
{
	float3 entityPosition = getPosition();
	if (position != entityPosition)
	{
		float3 diff = position - entityPosition;
		float distance = mymath::getLength(diff);
		float3 moveDir = mymath::normalize(diff);
		velocity = moveDir * moveSpeed;
	}
}

bool Entity::raycast(Ray ray, RayHitPoint* hitPoint, ColliderState colliderState)
{
	return boxCollider->raycast(ray, hitPoint, colliderState);
}

void Entity::goToPosition(float3 position)
{
	moveTargets.clear();
	moveTargets.push_back(position);
}

void Entity::addMoveTarget(float3 position)
{
	moveTargets.push_back(position);
}

void Entity::clearMoveTargets()
{
	moveTargets.clear();
}

void Entity::rotateViewDirectionTo(float3 dir)
{

}

void Entity::movementToTargets2()
{
	if (moveTargets.size() > 0)
	{
		float3 entityPosition = getPosition();
		float3 diff = moveTargets[0] - entityPosition;
		float distance = mymath::getLength(diff);
		if (distance <= radiusOfPoint)
			moveTargets.erase(moveTargets.begin());
		else
			moveTo(moveTargets[0]);
	}
}

void Entity::movementToTargets()
{
	if (moveTargets.size() > 0)
	{
		float3 target = moveTargets[0];
		float3 entityPosition = getPosition();
		float3 diff = target - entityPosition;
		float distance = mymath::getLength(diff);

		if (mymath::pointIntersected(oldPosition, entityPosition, target, radiusOfPoint))
		{
			float3 moveDirection = mymath::normalize(entityPosition - oldPosition);
			oldPosition = entityPosition;
			setPosition(target);
			moveTargets.erase(moveTargets.begin());
			if (moveSpeed <= maxMoveSpeedToNotLoseVelocity)
				velocity -= moveDirection * moveSpeed;
			else
				velocity = {};
		}
		else
		{
			oldPosition = entityPosition;
			moveTo(target);
		}
	}
}

void Entity::update()
{
	movementToTargets();
	setPosition(getPosition() + velocity * world->renderWindow->graphics->deltaTime);
}

void Entity::draw(RenderTarget* renderTarget, RenderState state)
{
	update();
	state.modelMatrix = modelMatrix * state.modelMatrix;
	renderTarget->draw(model, state);
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