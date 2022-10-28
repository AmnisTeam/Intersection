#pragma once
#include "Command.h"

class ObjectInWorld;

class CommandMoveTo : public Command
{
public:

	const static float minDistanceUpdate;
	const static float minTimeUpdate;
	const static float maxTimeUpdate;
	float timer = 0;

	ObjectInWorld* target;
	float toDistance;

	CommandMoveTo(ObjectInWorld* target, float toDistance);
	~CommandMoveTo();

	virtual void start() override;
	virtual void update() override;
	virtual void end() override;
};

