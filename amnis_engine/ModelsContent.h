#pragma once
#include "Model.h"

class ModelsContent
{
public:
	Model* sphere;
	Model* plane;
	Model* tree;
	Model* ghosthz;

	ModelsContent(RenderWindow* renderWindow);
	~ModelsContent();
};

