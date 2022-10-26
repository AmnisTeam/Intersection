#include "CommandSystem.h"

CommandSystem::CommandSystem(Entity* parent)
{
	this->parent = parent;
}

CommandSystem::~CommandSystem()
{
	for (auto& command : commands)
		delete command;
}

void CommandSystem::addCommand(Command* command)
{
	commands.push_back(command);
	command->commandSystem = this;
	if (commands.size() == 1)
		command->start();
}

void CommandSystem::popCommand()
{
	commands.pop_front();
	if (commands.size() > 0)
		commands.front()->start();
}

void CommandSystem::toEndCommand()
{
	endCommand = true;
}

void CommandSystem::update()
{
	if(!commands.empty())
		commands.front()->update();

	if (endCommand)
	{
		commands.front()->end();
		popCommand();
		endCommand = false;
	}
}
