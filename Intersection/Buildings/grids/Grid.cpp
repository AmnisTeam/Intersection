#include "Grid.h"
#include <list>

Grid::Grid(float sizeElementX, float sizeElementY)
{
	this->sizeElementX = sizeElementX;
	this->sizeElementY = sizeElementY;
}

bool Grid::setBuilding(Building* building)
{
	bool haveObstacle = false;
	for (int x = building->getPosX(); x < building->getPosX() + building->getWidth(); x++)
	{
		for (int y = building->getPosY(); y < building->getPosY() + building->getHeight(); y++)
		{
			if (element.find({x, y}) != element.end())
			{
				haveObstacle = element[{x, y}]->getObstacle();
				if (haveObstacle)
					break;
			}
		}
		if (haveObstacle)
			break;
	}

	if(!haveObstacle)
		for(int x = building->getPosX(); x < building->getPosX() + building->getWidth(); x++)
			for (int y = building->getPosY(); y < building->getPosY() + building->getHeight(); y++)
			{
				if (element.find({x, y}) == element.end())
					element[{x, y}] = new GridElement();
				element[{x, y}]->setBuilding(building);
			}

	return !haveObstacle;
}

void Grid::unsetBuilding(Building* building)
{
	int pX = building->getPosX();
	int pY = building->getPosY();
	
	int width = building->getWidth();
	int height = building->getHeight();

	for(int x = pX; x < pX + width; x++)
		for (int y = pY; y < pY + height; y++)
			if (element.find({ x, y }) != element.end())
			{
				delete element[{x, y}];
				element.erase({ x, y });
			}
}

void Grid::setObstacle(int x, int y)
{
	bool have = element.find({ x, y }) != element.end();
	GridElement* gridElement = nullptr;
	if (have)
		gridElement = element[{x, y}];
	else
	{
		gridElement = new GridElement();
		element[{x, y}] = gridElement;
	}

	gridElement->setObstacle(true);
}

bool Grid::unsetObstacle(int x, int y)
{
	bool have = element.find({ x, y }) != element.end();
	if (have)
	{
		GridElement* gridElement = element[{x, y}];
		if (gridElement->getBuilding() == nullptr)
		{
			gridElement->setObstacle(false);
			return true;
		}
		else
			return false;
	}
	else
		return true;
}

bool Grid::getGridElement(int x, int y, GridElement** gridElement)
{
	bool have = element.find({ x, y }) != element.end();
	if (have)
		*gridElement = element[{x, y}];
	else
	{
		*gridElement = nullptr;
	}
	return have;
}

int2* Grid::findPath(int2 point1, int2 point2, int* countGrids)
{
	/*int currentX = point1.x;
	int currentY = point1.y;*/

	/**countGrids = 3;
	return g;*/
	/*std::vector<GridElement*> memory;
	GridElement* around[3][3];
	int green[3][3];
	int blue[3][3];
	int red[3][3];

	int prevGreen[3][3];
	int prevBlue[3][3];
	int prevRed[3][3];*/
	/*getGridElement(point1.x - 1, point1.y - 1, &around[0]);
	getGridElement(point1.x, point1.y - 1, &around[1]);
	getGridElement(point1.x + 1, point1.y - 1, &around[2]);
	getGridElement(point1.x - 1, point1.y, &around[3]);
	getGridElement(point1.x + 1, point1.y, &around[4]);
	getGridElement(point1.x - 1, point1.y + 1, &around[5]);
	getGridElement(point1.x, point1.y + 1, &around[6]);
	getGridElement(point1.x + 1, point1.y + 1, &around[7]);*/
	/*int id1 = 0, id2 = 0;
	for (int x = currentX - 1; x <= currentX + 1; x++) {
		for (int y = currentY - 1; y <= currentY + 1; y++) {
			if (!(x == currentX && y == currentY) && getGridElement(x, y, &around[id1][id2]))
			{

				if ((id1 == 0 && id2 == 0) || (id1 == 0 && id2 == 2) || (id1 == 2 && id2 == 0) || (id1 == 2 && id2 == 2))
				{
					green[id1][id2] = 14;
					prevGreen[id1][id2] = 14;
				}
				else
				{
					green[id1][id2] = 10;
					prevGreen[id1][id2] = 10;
				}

				blue[id1][id2] = (abs(point2.x - x) + abs(point2.y - y)) * 10;
				prevBlue[id1][id2] = blue[id1][id2];

				red[id1][id2] = green[id1][id2] + blue[id1][id2];
				prevRed[id1][id2] = red[id1][id2];
			}
			id2++;
		}
		id2 = 0;
		id1++;
	}

	int prev = 10000, minRed = red[0][0];
	int idMinX = 0, idMinY = 0;
	id1 = 0, id2 = 0;
	for (int x = currentX - 1; x <= currentX + 1; x++) {
		for (int y = currentY - 1; y <= currentY + 1; y++) {
			if (!(x == currentX && y == currentY))
			{
				prev = red[id1][id2];
				if (minRed > prev)
				{
					minRed = red[id1][id2];
					idMinX = id1;
					idMinY = id2;
				}
			}
			id2++;
		}
		id2 = 0;
		id1++;
	}

	currentX += idMinX - 1;
	currentY += idMinY - 1;






	while (currentX != point2.x || currentY != point2.y)
	{
		int id1 = 0, id2 = 0;
		for (int x = currentX - 1; x <= currentX + 1; x++) {
			for (int y = currentY - 1; y <= currentY + 1; y++) {
				if (!(x == currentX && y == currentY) && getGridElement(x, y, &around[id1][id2]))
				{

					if (((id1 == 0 && id2 == 0) || (id1 == 0 && id2 == 2) || (id1 == 2 && id2 == 0) || (id1 == 2 && id2 == 2)))
					{
						if (prevGreen[id1][id2])
						green[id1][id2] = prevGreen[id1][id2] + 14;
					}
					else
					{
						int temp = prevGreen[id1][id2] + 10;
						green[id1][id2] = 10;
					}

					blue[id1][id2] = (abs(point2.x - x) + abs(point2.y - y)) * 10;


					red[id1][id2] = green[id1][id2] + blue[id1][id2];

				}
				id2++;
			}
			id2 = 0;
			id1++;
		}

		int prevRed = 10000, minRed = red[0][0];
		int idMinX = 0, idMinY = 0;
		id1 = 0, id2 = 0;
		for (int x = currentX - 1; x <= currentX + 1; x++) {
			for (int y = currentY - 1; y <= currentY + 1; y++) {
				if (!(x == currentX && y == currentY))
				{
					prevRed = red[id1][id2];
					if (minRed > prevRed)
					{
						minRed = red[id1][id2];
						idMinX = id1;
						idMinY = id2;
					}
				}
				id2++;
			}
			id2 = 0;
			id1++;
		}

		currentX += idMinX - 1;
		currentY += idMinY - 1;
	}*/


	/*nodes = new sNode[nMapWidth * nMapHeight];
	for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
		{
			nodes[y * nMapWidth + x].x = x;
			nodes[y * nMapWidth + x].y = y;
			nodes[y * nMapWidth + x].bObstacle = false;
			nodes[y * nMapWidth + x].parent = nullptr;
			nodes[y * nMapWidth + x].bVisited = false;
		}*/

	//for (int x = 0; x < nMapWidth; x++)
	//	for (int y = 0; y < nMapHeight; y++)
	//	{
	//		if (y > 0)
	//			nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 0)]);
	//		if (y < nMapHeight - 1)
	//			nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 0)]);
	//		if (x > 0)
	//			nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x - 1)]);
	//		if (x < nMapWidth - 1)
	//			nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 0) * nMapWidth + (x + 1)]);

	//		// We can also connect diagonally
	//		if (y > 0 && x > 0)
	//			nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x - 1)]);
	//		if (y < nMapHeight - 1 && x>0)
	//			nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x - 1)]);
	//		if (y > 0 && x < nMapWidth - 1)
	//			nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y - 1) * nMapWidth + (x + 1)]);
	//		if (y < nMapHeight - 1 && x < nMapWidth - 1)
	//			nodes[y * nMapWidth + x].vecNeighbours.push_back(&nodes[(y + 1) * nMapWidth + (x + 1)]);
	//		
	//	}













	std::list <sNode> spisok;
	nodes = new sNode[1];
	

	nodeStart = &nodes[(nMapHeight / 2) * nMapWidth + 1];
	nodeEnd = &nodes[(nMapHeight / 2) * nMapWidth + nMapWidth - 2];

	nodeStart->x = point1.x;
	nodeStart->y = point1.y;
	nodes[0].x = point1.x;
	nodes[0].y = point1.y;
	nodes[0].nodeId = 0;
	spisok.push_front(nodes[0]);

	nodeEnd->x = point2.x;
	nodeEnd->y = point2.y;

	//nodes[nSelectedNodeY * nMapWidth + nSelectedNodeX].bObstacle = true;


	/*for (int x = 0; x < nMapWidth; x++)
		for (int y = 0; y < nMapHeight; y++)
		{
			nodes[y * nMapWidth + x].bVisited = false;
			nodes[y * nMapWidth + x].fGlobalGoal = INFINITY;
			nodes[y * nMapWidth + x].fLocalGoal = INFINITY;
			nodes[y * nMapWidth + x].parent = nullptr;
		}*/

	auto distance = [](sNode* a, sNode* b)
	{
		return sqrtf((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
	};

	auto heuristic = [distance](sNode* a, sNode* b) 
	{
		return distance(a, b);
	};

	sNode* nodeCurrent = nodeStart;
	nodeStart->fLocalGoal = 0.0f;
	nodeStart->fGlobalGoal = heuristic(nodeStart, nodeEnd);

	std::list<sNode*> listNotTestedNodes;
	listNotTestedNodes.push_back(nodeStart);

	/*nodes[9].bObstacle = true;
	nodes[10].bObstacle = true;
	nodes[17].bObstacle = true;*/

	int countNodes = 1;
	while (!listNotTestedNodes.empty() && nodeCurrent != nodeEnd)
	{



		//ѕо моему с изначальной инициализацией будет работать быстрее тк не придетс€ 
		//проходить циклом по ближайшим элементам чтобы пон€ть инициализированы они или нет



		//—оздание элементов вокруг
		for (int i = nodeCurrent->x - 1; i <= nodeCurrent->x + 1; i++)
			for (int j = nodeCurrent->y - 1; j <= nodeCurrent->y + 1; j++)
			{
				if (!(i == nodeCurrent->x && j == nodeCurrent->y)) //не центр
				{
					nodes = new sNode[1];					//не нужно пересоздавать список
					nodes[0].x = i;
					nodes[0].y = j;
					nodes[0].nodeId = countNodes;
					spisok.push_front(nodes[0]);
					countNodes++;
				}
				/*else if ()*/
			}

		//—в€зывание списка



		listNotTestedNodes.sort([](const sNode* lhs, const sNode* rhs) { return lhs->fGlobalGoal < rhs->fGlobalGoal; });

		while (!listNotTestedNodes.empty() && listNotTestedNodes.front()->bVisited)
			listNotTestedNodes.pop_front();

		if (listNotTestedNodes.empty())
			break;

		nodeCurrent = listNotTestedNodes.front();
		nodeCurrent->bVisited = true;

		for (auto nodeNeighbour : nodeCurrent->vecNeighbours)
		{

			if (!nodeNeighbour->bVisited && nodeNeighbour->bObstacle == 0)
				listNotTestedNodes.push_back(nodeNeighbour);


			float fPossiblyLowerGoal = nodeCurrent->fLocalGoal + distance(nodeCurrent, nodeNeighbour);

			if (fPossiblyLowerGoal < nodeNeighbour->fLocalGoal)
			{
				nodeNeighbour->parent = nodeCurrent;
				nodeNeighbour->fLocalGoal = fPossiblyLowerGoal;
				nodeNeighbour->fGlobalGoal = nodeNeighbour->fLocalGoal + heuristic(nodeNeighbour, nodeEnd);
			}
		}
	}

	int cntGrids = 0;
	if (nodeEnd != nullptr)
	{
		sNode* p = nodeEnd;
		while (p->parent != nullptr)
		{
			cntGrids++;
			p = p->parent;
		}
	}


	int2* path = new int2[cntGrids];

	int idCntGrids = 0;
	if (nodeEnd != nullptr)
	{
		sNode* p = nodeEnd;
		while (p->parent != nullptr)
		{
			int a = p->x;
			int b = p->y;
			path[cntGrids - idCntGrids - 1].x = a;
			path[cntGrids - idCntGrids - 1].y = b;
			p = p->parent;
			idCntGrids++;
		}
	}



	return path;
}
