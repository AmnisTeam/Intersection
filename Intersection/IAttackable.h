#pragma once

class Healthable;

class IAttackable
{
public:

	virtual void attack(Healthable* healthable) = 0;
};

