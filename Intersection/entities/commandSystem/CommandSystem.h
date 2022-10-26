#pragma once
#include <iostream>
#include <deque>
#include "commands/Command.h"
#include "../../IUpdateable.h"

using namespace std;

class Entity;

class CommandSystem : public IUpdatable
{
public:
	deque<Command*> commands;
	bool endCommand = false;

	CommandSystem(Entity* parent);
	~CommandSystem();

	void addCommand(Command* command);
	void popCommand();
	void toEndCommand();

	// Унаследовано через IUpdatable
	virtual void update() override;
};

