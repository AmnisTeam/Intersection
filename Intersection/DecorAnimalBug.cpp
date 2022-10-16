#include "DecorAnimalBug.h"
#include "World.h"

DecorAnimalBug::DecorAnimalBug(World* world, float3 spotPosition, float radius) : DecorAnimal(world, ModelsContent::bug, spotPosition, radius)
{
	model->setTexture(TexturesContent::flatNormalMap, 1);
	setRotation({0, -PI / 2, 0});
}

void DecorAnimalBug::update()
{
	DecorAnimal::update();
	//if (mymath::getLength(moveSystem->movement) != 0)
	//{
	//	float3 movementDir = mymath::normalize(moveSystem->movement);
	//	float3 lookDir = getDirectionRotation();
	//	float angle = acos(mymath::dot(movementDir, lookDir));
	//	if(angle > speedRotation * world->renderWindow->graphics->deltaTime * 2)
	//		setDirectionRotation(mymath::circleLerp(getDirectionRotation(), mymath::normalize(moveSystem->movement), speedRotation * world->renderWindow->graphics->deltaTime));
	//}

	float alpha = ((rand() % 1000) / static_cast<float>(1000)) * 2*PI;
	float radius = ((rand() % 1000) / static_cast<float>(1000)) * this->radius_;

	float x = cos(alpha) * radius;
	float z = sin(alpha) * radius;

	float chanceStopBug = 0.2f;
	timer += world->renderWindow->graphics->deltaTime;
	k += 0.01f;

	if (getMoveTargetsCount() == 0 && timer > 1) {
		if ((rand() % 1000) / static_cast<float>(1000) < chanceStopBug)
			timer = 0;
		else
			addMoveTarget(this->spotPosition_ + float3{ x,0,z });
	}
}