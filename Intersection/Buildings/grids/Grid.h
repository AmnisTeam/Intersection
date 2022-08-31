#pragma once
#include "Transformable.h"
#include "GridElement.h"
#include "../Building.h"
#include <map>
#include <string>
#include <algorithm>
#include <list>

class Grid
{
public:
	float sizeElementX;
	float sizeElementY;

	std::map<std::string, GridElement*> element;
	Grid(float sizeElementX, float sizeElementY);

	bool setBuilding(Building* building);
	void unsetBuilding(Building* building);

	void setObstacle(int x, int y);
	bool unsetObstacle(int x, int y);

	bool getGridElement(int x, int y, GridElement** gridElement);

	std::string getKey(int x, int y);

	struct Node
	{
		int x;
		int y;
		float blue;
		float green;
		float weight;
		int direction;
	};

	int2* astar(int2 point1, int2 point2, int* countGrids);

	int2* findPathInOneDirection(
		int2 point1,
		int2 point2,
		int* countGrids,
		int countStep,
		std::map<std::string, Node*>* nodes,
		std::map<std::string, Node*>* pathNodes,
		std::list<Node*>* listNotTestedNodes,
		Node*& activeNode);
	int2* findPath(int2 point1, int2 point2, int* countGrids, int countStep = 1000);
};

