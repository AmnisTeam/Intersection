#pragma once
#include "Skill.h"
#include "../IUpdateable.h"
#include "../World.h"

class SkillSpawner : public Skill, public IUpdatable
{
public:
	float timer = 0;


	void active() override;
	void passive() override;

	// ������������ ����� IUpdatable
	virtual void update() override;

private:


	

};