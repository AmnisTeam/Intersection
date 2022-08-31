#include "Grid.h"

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
			if (element.find(getKey(x, y)) != element.end())
			{
				GridElement* gridElement = element[getKey(x, y)];
				haveObstacle = gridElement->getObstacle();
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
				if (element.find(getKey(x, y)) == element.end())
					element[getKey(x, y)] = new GridElement();
				element[getKey(x, y)]->setBuilding(building);
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
			if (element.find(getKey(x, y)) != element.end())
			{
				delete element[getKey(x, y)];
				element.erase(getKey(x, y));
			}
}

void Grid::setObstacle(int x, int y)
{
	bool have = element.find(getKey(x, y)) != element.end();
	GridElement* gridElement = nullptr;
	if (have)
		gridElement = element[getKey(x, y)];
	else
	{
		gridElement = new GridElement();
		element[getKey(x, y)] = gridElement;
	}

	gridElement->setObstacle(true);
}

bool Grid::unsetObstacle(int x, int y)
{
	bool have = element.find(getKey(x, y)) != element.end();
	if (have)
	{
		GridElement* gridElement = element[getKey(x, y)];
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
	bool have = element.find(getKey(x, y)) != element.end();
	if (have)
		*gridElement = element[getKey(x, y)];
	else
	{
		*gridElement = nullptr;
	}
	return have;
}

std::string Grid::getKey(int x, int y)
{
	return std::to_string(x) + "+" + std::to_string(y);
}

int2* Grid::astar(int2 point1, int2 point2, int* countGrids)
{
	struct Node
	{
		int x;
		int y;
		float blue;
		float green;
		float weight;
		int direction;
	};
	std::map<std::string, Node*> nodes;
	std::map<std::string, Node*> pathNodes;
	std::list<Node*> listNotTestedNodes;

	Node* startNode = new Node();
	Node* activeNode = startNode;
	activeNode->x = point1.x;
	activeNode->y = point1.y;
	activeNode->blue = 0;
	activeNode->green = 0;
	activeNode->weight = 0;

	nodes[getKey(point1.x, point1.y)] = startNode;

	while (!(activeNode->x == point2.x && activeNode->y == point2.y))
	{
		int id = 0;
		for (int x = activeNode->x - 1; x <= activeNode->x + 1; x++)
			for (int y = activeNode->y - 1; y <= activeNode->y + 1; y++)
			{
				if (!(x == activeNode->x && y == activeNode->y))
					if (pathNodes.find(getKey(x, y)) == pathNodes.end())
					{
						bool addNode = element.find(getKey(x, y)) == element.end();
						if (!addNode)
							addNode = !element[getKey(x, y)]->getObstacle();
						if (addNode)
						{
							Node node;
							node.x = x;
							node.y = y;
							node.direction = id;
							node.green = (id % 2 == 0 ? 14 : 10) + activeNode->green;
							node.blue = (abs(point2.x - x) + abs(point2.y - y)) * 10;
							node.weight = node.green + node.blue;

							addNode = nodes.find(getKey(x, y)) == nodes.end();
							if (!addNode)
							{
								Node* nodeInPath = nodes[getKey(x, y)];
								if (node.weight < nodeInPath->weight)
									*nodeInPath = node;
							}
							else
							{
								Node* pushNode = new Node(node);
								listNotTestedNodes.push_back(pushNode);
								nodes[getKey(x, y)] = pushNode;
							}
						}
					}
				id++;
			}

		if (listNotTestedNodes.empty())
			return nullptr;

		listNotTestedNodes.sort([](const Node* l, const Node* r) {return l->weight < r->weight; });

		Node* frontNode = listNotTestedNodes.front();
		listNotTestedNodes.pop_front();
		pathNodes[getKey(frontNode->x, frontNode->y)] = frontNode;

		activeNode = frontNode;
	}

	std::vector<int2> reversePath;
	while (activeNode)
	{
		reversePath.push_back({ activeNode->x, activeNode->y });
		int pX = activeNode->x - (activeNode->direction / 3 - 1);
		int pY = activeNode->y - (activeNode->direction % 3 - 1);
		activeNode = pathNodes[getKey(pX, pY)];
	}
	reversePath.push_back({ point1.x, point1.y });

	int2* path = new int2[reversePath.size()];
	for (int x = reversePath.size() - 1; x >= 0; x--)
		path[x] = reversePath[x];

	*countGrids = reversePath.size();

	for (auto i = nodes.begin(); i != nodes.end(); ++i)
		delete i->second;

	delete startNode;

	return path;
}

int2* Grid::findPathInOneDirection(
	int2 point1, 
	int2 point2, 
	int* countGrids,
	int countStep,
	std::map<std::string, Node*>* nodes, 
	std::map<std::string, Node*>* pathNodes, 
	std::list<Node*>* listNotTestedNodes,
	Node*& activeNode)
{
	int count = 0;
	while (!(activeNode->x == point2.x && activeNode->y == point2.y) && count < countStep)
	{
		int id = 0;
		for (int x = activeNode->x - 1; x <= activeNode->x + 1; x++)
			for (int y = activeNode->y - 1; y <= activeNode->y + 1; y++)
			{
				if (!(x == activeNode->x && y == activeNode->y))
					if (pathNodes->find(getKey(x, y)) == pathNodes->end())
					{
						bool addNode = element.find(getKey(x, y)) == element.end();
						if (!addNode)
							addNode = !element[getKey(x, y)]->getObstacle();
						if (addNode)
						{
							Node node;
							node.x = x;
							node.y = y;
							node.direction = id;
							node.green = (id % 2 == 0 ? 14 : 10) + activeNode->green;
							node.blue = (abs(point2.x - x) + abs(point2.y - y)) * 10;
							node.weight = node.green + node.blue;

							addNode = nodes->find(getKey(x, y)) == nodes->end();
							if (!addNode)
							{
								Node* nodeInPath = (*nodes)[getKey(x, y)];
								if (node.weight < nodeInPath->weight)
									*nodeInPath = node;
							}
							else
							{
								Node* pushNode = new Node(node);
								listNotTestedNodes->push_back(pushNode);
								(*nodes)[getKey(x, y)] = pushNode;
							}
						}
					}
				id++;
			}

		if (listNotTestedNodes->empty())
		{
			*countGrids = 0;
			return nullptr;
		}

		listNotTestedNodes->sort([](const Node* l, const Node* r) {return l->weight < r->weight; });

		Node* frontNode = listNotTestedNodes->front();
		listNotTestedNodes->pop_front();
		(*pathNodes)[getKey(frontNode->x, frontNode->y)] = frontNode;
		
		activeNode = frontNode;
		count++;
	}

	Node* pathNode = activeNode;
	std::vector<int2> reversePath;
	while (pathNode)
	{
		reversePath.push_back({ pathNode->x, pathNode->y});
		int pX = pathNode->x - (pathNode->direction / 3 - 1);
		int pY = pathNode->y - (pathNode->direction % 3 - 1);
		pathNode = (*pathNodes)[getKey(pX, pY)];
	}
	reversePath.push_back({ point1.x, point1.y });

	int2* path = new int2[reversePath.size()];
	for (int x = 0; x < reversePath.size(); x++)
		path[x] = reversePath[reversePath.size() - 1 - x];

	*countGrids = reversePath.size();

	return path;
}

int2* Grid::findPath(int2 point1, int2 point2, int* countGrids, int countStep)
{
	std::map<std::string, Node*> forwardNodes;
	std::map<std::string, Node*> forwardPathNodes;
	std::list<Node*> forwardListNotTestedNodes;

	Node* forwardActiveNode = new Node();
	forwardActiveNode->x = point1.x;
	forwardActiveNode->y = point1.y;
	forwardActiveNode->blue = 0;
	forwardActiveNode->green = 0;
	forwardActiveNode->weight = 0;

	forwardNodes[getKey(point1.x, point1.y)] = forwardActiveNode;

	std::map<std::string, Node*> backwardNodes;
	std::map<std::string, Node*> backwardPathNodes;
	std::list<Node*> backwardListNotTestedNodes;

	Node* backwardActiveNode = new Node();
	backwardActiveNode->x = point2.x;
	backwardActiveNode->y = point2.y;
	backwardActiveNode->blue = 0;
	backwardActiveNode->green = 0;
	backwardActiveNode->weight = 0;

	backwardNodes[getKey(point2.x, point2.y)] = backwardActiveNode;

	bool forward = true;
	int2* path = nullptr;
	int count = 0;
	bool pathFound = false;
	do
	{
		if (forward)
		{
			path = findPathInOneDirection(point1, point2, &count, countStep, &forwardNodes, &forwardPathNodes, &forwardListNotTestedNodes, forwardActiveNode);
			if (path)
				pathFound = path[count - 1].x == point2.x && path[count - 1].y == point2.y;
			else
				pathFound = false;
		}
		else
		{
			path = findPathInOneDirection(point2, point1, &count, countStep, &backwardNodes, &backwardPathNodes, &backwardListNotTestedNodes, backwardActiveNode);
			if (path)
				pathFound = path[count - 1].x == point1.x && path[count - 1].y == point1.y;
			else
				pathFound = false;
		}
		forward = !forward;

	} while (path && !pathFound);
	forward = !forward;

	if (!forward && path)
	{
		for (int x = 0; x < count / 2; x++)
		{
			int2 temp = path[x];
			path[x] = path[count - 1 - x];
			path[count - 1 - x] = temp;
		}
	}

	for (auto it = forwardNodes.begin(); it != forwardNodes.end(); ++it)
		delete it->second;

	for (auto it = backwardNodes.begin(); it != backwardNodes.end(); ++it)
		delete it->second;

	*countGrids = count;
	return path;
}
