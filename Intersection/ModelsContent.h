#pragma once
#include "AmnModel.h"

class RenderWindow;

class ModelsContent
{
public:
	static AmnModel* sphere;
	static AmnModel* plane;
	static AmnModel* tree;
	static AmnModel* ghosthz;
	static AmnModel* box;
	static AmnModel* dragon;
	static AmnModel* wolf;
	static AmnModel* knight;
	static AmnModel* bug;
	static RenderWindow* renderWindow;

	//������� (10 ����)
	static AmnModel* treeModels[10];

	static void load(RenderWindow* renderWindow);
};

