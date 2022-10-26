#pragma once
#include "../../Healthable.h"
#include <deque>
#include "commands/Command.h"

using namespace std;

class Commandable : public Healthable
{
public:
	deque<Command*> commands;
	bool endCommand = false;

	Commandable(World* world, float health, float mana);

	void addCommand(Command* command);
	void popCommand();
	void toEndCommand();

	// Унаследовано через IUpdatable
	virtual void update() override;
};

