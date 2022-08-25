#pragma once
#include "Transformable.h"
#include "GridElement.h"
#include "../Building.h"
#include <map>

class Grid
{
public:
	float sizeElementX;
	float sizeElementY;

	std::map<int2, GridElement*> element;
	Grid(float sizeElementX, float sizeElementY);

	bool setBuilding(Building* building);
	void unsetBuilding(Building* building);

	void setObstacle(int x, int y);
	bool unsetObstacle(int x, int y);

	bool getGridElement(int x, int y, GridElement** gridElement);



	int2* findPath(int2 point1, int2 point2, int* countGrids);
	//bool Solve_AStar();

private:

	struct sNode
	{
		bool bObstacle = false;				// Is the node an obstruction?
		bool bVisited = false;				// Have we searched this node before?
		float fGlobalGoal = INFINITY;		// Distance to goal so far
		float fLocalGoal = INFINITY;			// Distance to goal if we took the alternative route
		int nodeId;
		int x;								// Nodes position in 2D space
		int y;
		std::vector<sNode*> vecNeighbours;	// Connections to neighbours
		sNode* parent = nullptr;			// Node connecting to this node that offers shortest parent
	};

	sNode *nodes = nullptr;
	int nMapWidth = 7;
	int nMapHeight = 5;

	sNode *nodeStart = nullptr;
	sNode *nodeEnd = nullptr;
	
};