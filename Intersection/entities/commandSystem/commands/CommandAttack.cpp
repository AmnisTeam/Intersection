#include "CommandAttack.h"
#include "../../Entity.h"

CommandAttack::CommandAttack(ObjectInWorld* target, float toDistance) : CommandMoveTo(target, toDistance)
{
}

CommandAttack::CommandAttack(float3 target, float toDistance) : CommandMoveTo(nullptr, toDistance)
{
	this->targetPoint = target;
}

void CommandAttack::start()
{
	CommandMoveTo::start();
	if(!target)
		dynamic_cast<IMovable*>(commandable)->getMoveSystem()->goToPositionAstar(targetPoint);
}

void CommandAttack::update()
{
	if (target)
	{
		CommandMoveTo::update();
	}
	else
	{
		if (dynamic_cast<IMovable*>(commandable)->getMoveSystem()->getMoveTargetsCount() == 0)
			toEndCommand();
	}
}

void CommandAttack::end()
{
	CommandMoveTo::end();
}


