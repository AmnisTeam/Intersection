#include "Inventory.h"

Inventory::Inventory()
{
	//elements = std::vector<InventoryElement*>();
}

std::vector<InventoryElement*> Inventory::getElements() { return elements; };
void Inventory::addElement(InventoryElement* element) { elements.push_back(element); };
void Inventory::clickElement(int index) { elements[index]->active(); }

void Inventory::update()
{
	for (auto i : elements) {
		i->update();
	}
}
;