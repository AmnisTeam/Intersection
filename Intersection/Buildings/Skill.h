#pragma once
#include "../World.h"

class Skill
{
public:
	World* world;

	virtual void active();
	virtual void passive();

private:

};

