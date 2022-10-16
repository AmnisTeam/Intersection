#pragma once
#include "../IUpdateable.h"

class InventoryElement : public IUpdatable
{
public:
	virtual void active();

	// ������������ ����� IUpdatable
	virtual void update() override;
};

