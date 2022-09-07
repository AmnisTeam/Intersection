#include "DecorAnimalBug.h"
#include "World.h"

DecorAnimalBug::DecorAnimalBug(World* world, float3 spotPosition, float radius) : DecorAnimal(world, ModelsContent::sphere, spotPosition, radius)
{

}

void DecorAnimalBug::update()
{
	DecorAnimal::update();

	float alpha = ((rand() % 1000) / static_cast<float>(1000)) * 2*PI;
	float radius = ((rand() % 1000) / static_cast<float>(1000)) * this->radius_;

	float x = cos(alpha) * radius;
	float z = sin(alpha) * radius;

	float chanceStopBug = 0.2f;
	timer += world->renderWindow->graphics->deltaTime;

	if (getMoveTargetsCount() == 0 && timer > 1) {
		if ((rand() % 1000) / static_cast<float>(1000) < chanceStopBug)
			timer = 0;
		else
			addMoveTarget(this->spotPosition_ + float3{ x,0,z });
	}
}
