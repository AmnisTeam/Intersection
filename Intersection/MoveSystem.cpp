#include "MoveSystem.h"
#include "ObjectInWorld.h"
#include "World.h"

MoveSystem::MoveSystem(ObjectInWorld* parent)
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

void MoveSystem::rotateViewDirectionTo(float3 dir, double deltaTime)
{
	dir = mymath::normalize(dir);
	float3 lookDir = parent_->getDirectionRotation();
	float angle = acos(mymath::dot(dir, lookDir));
	if (angle > turningSpeed * deltaTime * 2)
		parent_->setDirectionRotation(mymath::circleLerp(lookDir, dir, turningSpeed * deltaTime));
}

void MoveSystem::updateMovableSystem(double deltaTime)
{
	float3 parentPosition = parent_->getPosition();

	if(tempPosition_ != parentPosition)
		setOldPosition(parentPosition);

	movementToTargets();

	velocity += movement;
	
	if(mymath::getLength(movement) != 0)
		rotateViewDirectionTo(movement, deltaTime);
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

void MoveSystem::goToPositionAstar(float3 position)
{
	int countGrids;
	float3* path = parent_->world->grid->findShortestPath(parent_->getPosition(), position, &countGrids);

	for (int y = 0; y < countGrids; y++)
		addMoveTarget({ (float)path[y].x, 0, (float)path[y].z });

	delete path;
}
