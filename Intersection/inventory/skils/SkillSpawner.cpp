#include "SkillSpawner.h"
#include "../../entities/Entity.h"
#include <stdlib.h>

SkillSpawner::SkillSpawner(World* world, Transformable* transformable, float spawnTime, int idEntity) : Skill(world, transformable)
{
	this->world = world;
	this->transformable = transformable;
	this->spawnTime = spawnTime;
	this->idEntity = idEntity;
}

void SkillSpawner::active()
{
	Skill::active();
	Entity* entity = world->registerEntities->createEntity(idEntity);
	float alpha = rand() / (float)RAND_MAX * 2 * PI;
	float r = rand() / (float)RAND_MAX;
	float3 randPos = { cos(alpha) * r, 0, sin(alpha) * r };
	entity->setPosition(transformable->getPosition() + randPos);
	world->addEntity(entity);

}

void SkillSpawner::passive()
{
	Skill::passive();
	timer += world->renderWindow->graphics->deltaTime;

	if (timer >= spawnTime) {
		timer = 0;
		active();
	}
}

void SkillSpawner::update()
{
	passive();
}