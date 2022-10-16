#pragma once
#include "InventoryItem.h"
#include <vector>
#include "../IUpdateable.h"

class Inventory : public IUpdatable
{
private:
	std::vector<InventoryElement*> elements;
public:
	Inventory();
	std::vector<InventoryElement*> getElements();
	void addElement(InventoryElement* element);
	void clickElement(int index);

	// Унаследовано через IUpdatable
	virtual void update() override;
};