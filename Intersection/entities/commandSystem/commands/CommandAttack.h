#pragma once
#include "CommandMoveTo.h"
#include <mymath.h>

class CommandAttack : public CommandMoveTo
{
public:
	float3 targetPoint = {};

	CommandAttack(ObjectInWorld* target, float toDistance);
	CommandAttack(float3 target, float toDistance);

	virtual void start() override;
	virtual void update() override;
	virtual void end() override;
};

