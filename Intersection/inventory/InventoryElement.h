#pragma once
#include "../IUpdateable.h"

class InventoryElement : public IUpdatable
{
public:
	virtual void active();

	// Унаследовано через IUpdatable
	virtual void update() override;
};

