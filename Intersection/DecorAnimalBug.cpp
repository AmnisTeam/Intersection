#include "DecorAnimalBug.h"
#include "World.h"

DecorAnimalBug::DecorAnimalBug(World* world, float3 spotPosition, float radius) : DecorAnimal(world, ModelsContent::bug, spotPosition, radius)
{
	model->setTexture(TexturesContent::flatNormalMap, 1);
}

void DecorAnimalBug::update()
{
	DecorAnimal::update();

	if (mymath::getLength(moveSystem->movement) != 0)
	{

	}

	//float3 r1 = mymath::getRotation(mymath::normalize(float3{ 1, 0, 0 }));
	//float3 r2 = mymath::getRotation(mymath::normalize(float3{ 0, 1, 0 }));
	//float3 r3 = mymath::getRotation(mymath::normalize(float3{ 0, 0, 1 }));
	if(mymath::getLength(moveSystem->movement) != 0)
		rot = mymath::getRotation(mymath::normalize(moveSystem->movement));

	if (mymath::getLength(moveSystem->movement) != 0)
	{
		float3 pos = getPosition();
		float3 focus = mymath::normalize(moveSystem->movement);
		rot = DirectX::XMMatrixLookAtLH(DirectX::XMVectorSet(0,0, 0, 0), DirectX::XMVectorSet(focus.x, focus.y, focus.z, 0), DirectX::XMVectorSet(0, 0, 1, 0));
	}

	//setRotation(rot);

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

void DecorAnimalBug::draw(RenderTarget* renderTarget, RenderState state)
{
	//state.modelMatrix = rot * state.modelMatrix;
	//modelMatrix = DirectX::XMMatrixRotationY(-PI/2) * modelMatrix;
	modelMatrix = rot * modelMatrix;
	DecorAnimal::draw(renderTarget, state);
}
