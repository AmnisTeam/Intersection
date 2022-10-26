#pragma once
#include "Transformable.h"

class World;

class ObjectInWorld : public Transformable
{
public:

	World* world;

	ObjectInWorld(World* world);
};

