#include "Command.h"
#include "../Commandable.h"

Command::Command()
{

}

Command::~Command()
{
}

void Command::toEndCommand()
{
	commandable->toEndCommand();
}

void Command::start()
{
}

void Command::update()
{
}

void Command::end()
{

}
