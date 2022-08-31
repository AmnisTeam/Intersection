#pragma once
#include <vector>

class Entity;
class World;

class RegisterEntities
{
public:
	World* world;
	std::vector<Entity*> entities;

	RegisterEntities(World* world);

	void addEntity(Entity* entity);
	Entity* createEntity(int id);
	void init();
};

