#include "Inventory.h"

std::vector<InventoryItem*> Inventory::getItems() { return items; };
void Inventory::addItem(InventoryItem* item) { items.push_back(item); };
void Inventory::clickItem(int index) { items[index]->handleClick(); };