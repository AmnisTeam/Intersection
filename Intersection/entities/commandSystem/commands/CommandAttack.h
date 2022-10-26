#pragma once
#include "Command.h"

class CommandAttack : public Command
{
public:

	CommandAttack();

	virtual void start() override;
	virtual void update() override;
	virtual void end() override;
};

