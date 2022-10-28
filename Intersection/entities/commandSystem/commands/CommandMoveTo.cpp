#include "CommandMoveTo.h"
#include "../Commandable.h"
#include "../../../World.h"

const float CommandMoveTo::minDistanceUpdate = 8;
const float CommandMoveTo::minTimeUpdate = 0.2f;
const float CommandMoveTo::maxTimeUpdate = 5;

CommandMoveTo::CommandMoveTo(ObjectInWorld* target, float toDistance)
{
	this->target = target;
	this->toDistance = toDistance;
}

CommandMoveTo::~CommandMoveTo()
{
}

void CommandMoveTo::start()
{
	Command::start();
	timer = 9999;
}

void CommandMoveTo::update()
{
	Command::update();
	
	float distanceToTarget = mymath::getLength(commandable->getPosition() - target->getPosition());
	float time = distanceToTarget <= minDistanceUpdate ? minTimeUpdate : maxTimeUpdate;

	timer += commandable->world->renderWindow->graphics->deltaTime;
	if (distanceToTarget > toDistance)
	{
		if (timer >= time)
		{
			dynamic_cast<IMovable*>(commandable)->getMoveSystem()->clearMoveTargets();
			dynamic_cast<IMovable*>(commandable)->getMoveSystem()->goToPositionAstar(target->getPosition());
			timer = 0;
		}
	}
	else
	{
		dynamic_cast<IMovable*>(commandable)->getMoveSystem()->clearMoveTargets();
	}
}

void CommandMoveTo::end()
{
	Command::end();

}
