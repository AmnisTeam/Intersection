#pragma once
#include "Model.h"
#include "decl.h"

class DirectLightSource : public Model
{
public:
	DECL DirectLightSource(Graphics* graphics, char* modelPath);
};

