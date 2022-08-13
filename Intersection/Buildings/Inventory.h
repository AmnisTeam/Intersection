#pragma once
#include "InventoryItem.h"
#include <vector>

class Inventory 
{
private:
	std::vector<InventoryItem*> items;
public:
	std::vector<InventoryItem*> getItems();
	void addItem(InventoryItem* item);
	void clickItem(int index);
};