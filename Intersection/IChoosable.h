#pragma once
#include "CompositeCollider.h"

class IChoosable
{
public:
	virtual Collider* getCollider() = 0;
};