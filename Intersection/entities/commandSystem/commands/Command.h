#pragma once
#include "../../../IUpdateable.h"

class Commandable;

class Command : public IUpdatable
{
public:
	Commandable* commandable;

	Command();
	~Command();

	void toEndCommand();

	virtual void start();
	virtual void update() override;
	virtual void end();
};

