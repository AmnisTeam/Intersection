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
	static RenderWindow* renderWindow;

	static void load(RenderWindow* renderWindow);
};

