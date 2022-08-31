#include "RegisterEntities.h"
#include "../World.h"
#include "Entity.h"
#include "EntityTree.h"

RegisterEntities::RegisterEntities(World* world)
{
	this->world = world;
	init();
}

void RegisterEntities::addEntity(Entity* entity)
{
	entity->id = entities.size();
	entities.push_back(entity);
}

Entity* RegisterEntities::createEntity(int id)
{
	Entity* entity = (Entity*)entities[id]->clone();
	entity->id = id;
	return entity;
}

void RegisterEntities::init()
{
	addEntity(new EntityTree(world));
}
