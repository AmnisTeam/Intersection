#include "SkillSpawner.h"

void SkillSpawner::active()
{
}

void SkillSpawner::passive()
{
	timer += world->renderWindow->graphics->deltaTime;





}

void SkillSpawner::update()
{
	passive();
}