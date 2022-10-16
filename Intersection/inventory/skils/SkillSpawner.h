#pragma once
#include "Skill.h"
#include "../../IUpdateable.h"
#include "../../World.h"
#include "../../entities/RegisterEntities.h"

class SkillSpawner : public Skill, public IUpdatable
{
public:
	float timer = 0;
	float spawnTime = 0;
	int idEntity = 0;

	SkillSpawner(World* world, Transformable* transformable, float spawnTime, int idEntity);

	void active() override;
	void passive() override;

	// Унаследовано через IUpdatable
	virtual void update() override;

private:


	

};