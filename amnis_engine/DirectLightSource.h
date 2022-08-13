#pragma once
#include "AmnModel.h"
#include "decl.h"

class DirectLightSource : public AmnModel
{
public:
	DECL DirectLightSource(Graphics* graphics, char* modelPath);
};

