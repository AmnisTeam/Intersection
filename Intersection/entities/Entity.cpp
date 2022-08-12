#include "Entity.h"

Entity::Entity(RenderWindow* renderWindow, AmnModel* model)
{
	this->renderWindow = renderWindow;
	this->model = new ModeledObject(renderWindow, model);
	oldPosition = getPosition();
	this->model->setTexture(TexturesContent::flatNormalMap, 1);
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
	setPosition(getPosition() + velocity * renderWindow->graphics->deltaTime);
}

void Entity::draw(RenderTarget* renderTarget, RenderState state)
{
	update();
	state.modelMatrix = modelMatrix * state.modelMatrix;
	renderTarget->draw(model, state);
}


