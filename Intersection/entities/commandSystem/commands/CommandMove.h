#pragma once
#include "Command.h"
#include "mymath.h"

class CommandMove : public Command
{
public:
	float3 target;

	CommandMove(float3 target);

	virtual void start() override;
	virtual void update() override;
	virtual void end() override;
};

