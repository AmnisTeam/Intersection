#pragma once
#include "AmnModel.h"
#include "decl.h"

class RenderWindow;
class DirectLightSource : public AmnModel
{
public:
	DECL DirectLightSource(RenderWindow* graphics, char* modelPath);
};

