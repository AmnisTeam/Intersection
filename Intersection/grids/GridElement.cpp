#include "GridElement.h"

GridElement::GridElement()
{
}

void GridElement::setBuild(void* build)
{
	this->build = build;
	haveObstacle = build != nullptr;
}

void GridElement::setObstacle(bool haveObstacle)
{
	if (build == nullptr)
		this->haveObstacle = haveObstacle;
}

void* GridElement::getBuild() const
{
	return build;
}

bool GridElement::getObstacle() const
{
	return haveObstacle;
}
