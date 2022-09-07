#include "MoveSystem.h"


MoveSystem::MoveSystem(Transformable* parent)
{
	parent_ = parent;
}

void MoveSystem::goToPosition(float3 position)
{
	moveTargets.clear();
	addMoveTarget(position);
}

void MoveSystem::addMoveTarget(float3 position)
{
	moveTargets.push_back(position); 
}

void MoveSystem::clearMoveTargets()
{
	moveTargets.clear();
}

void MoveSystem::rotateViewDirectionTo(float3 dir)
{
}

void MoveSystem::updateMovableSystem(double deltaTime)
{
	float3 parentPosition = parent_->getPosition();

	if(tempPosition_ != parentPosition)
		setOldPosition(parentPosition);

	movementToTargets();

	velocity += movement;
	
	setOldPosition(parentPosition);
	parent_->setPosition(parentPosition + velocity * deltaTime);
	tempPosition_ = parent_->getPosition();

	velocity -= movement;
}

void MoveSystem::setOldPosition(float3 oldPosition)
{
	oldPosition_ = oldPosition;
}

void MoveSystem::movementToTargets()
{
	if (moveTargets.size() > 0)
	{
		float3 target = moveTargets[0];
		float3 entityPosition = parent_->getPosition();
		float3 diff = target - entityPosition;
		float distance = mymath::getLength(diff);

		if (mymath::pointIntersected(oldPosition_, entityPosition, target, radiusOfPoint_))
		{
			float3 moveDirection = mymath::normalize(entityPosition - oldPosition_);
			parent_->setPosition(target);
			moveTargets.erase(moveTargets.begin());
			movement = {};
		}
		else
			moveTo(target);
	}
}

void MoveSystem::moveTo(float3 const position)
{
	float3 entityPosition = parent_->getPosition();

	bool alreadyAtPoint = (position == entityPosition);
	if (!alreadyAtPoint)
	{
		float3 diff = position - entityPosition;
		float distance = mymath::getLength(diff);
		float3 moveDir = mymath::normalize(diff);
		movement = moveDir * moveSpeed;
	}
}

int MoveSystem::getMoveTargetsCount()
{
	return moveTargets.size();
}
