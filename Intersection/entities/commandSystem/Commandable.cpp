#include "Commandable.h"

Commandable::Commandable(World* world, float health, float mana) : Healthable(world, health, mana)
{

}

void Commandable::addCommand(Command* command)
{
	commands.push_back(command);
	command->commandable = this;
	if (commands.size() == 1)
		command->start();
}

void Commandable::popCommand()
{
	commands.pop_front();
	if (commands.size() > 0)
		commands.front()->start();
}

void Commandable::toEndCommand()
{
	endCommand = true;
}

void Commandable::update()
{
	Healthable::update();
	if (!commands.empty())
		commands.front()->update();

	if (endCommand)
	{
		commands.front()->end();
		popCommand();
		endCommand = false;
	}
}
