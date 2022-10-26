#include "CommandMove.h"
#include "../CommandSystem.h"
#include "../../Entity.h"

CommandMove::CommandMove(float3 target)
{
	this->target = target;
}

void CommandMove::start()
{
	Command::start();
	dynamic_cast<IMovable*>(commandable)->getMoveSystem()->goToPositionAstar(target);
}

void CommandMove::update()
{
	Command::update();
	if (dynamic_cast<IMovable*>(commandable)->getMoveSystem()->getMoveTargetsCount() == 0)
		toEndCommand();
}

void CommandMove::end()
{
	Command::end();
}
