#pragma once
#include "CompositeCollider.h"

class IChoosable
{
public:
	virtual Collider* getCollider() = 0;
	virtual void* getObject() = 0;
};