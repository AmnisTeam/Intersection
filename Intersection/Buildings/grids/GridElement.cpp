#include "GridElement.h"

GridElement::GridElement()
{
}

bool GridElement::isWall(GridElement* gridElement)
{
	return gridElement == nullptr ? false : gridElement->getObstacle();
}

void GridElement::setBuilding(Building* building)
{
	this->building = building;
	haveObstacle = building != nullptr;
}

void GridElement::setObstacle(bool haveObstacle)
{
	if (building == nullptr)
		this->haveObstacle = haveObstacle;
}

Building* GridElement::getBuilding() const
{
	return building;
}

bool GridElement::getObstacle() const
{
	return haveObstacle;
}
