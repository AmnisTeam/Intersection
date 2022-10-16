#pragma once
#include "DecorAnimal.h"
#include "ModelsContent.h"

class DecorAnimalBug : public DecorAnimal
{
public:
	float timer = 0;
	float k = 0;

	DirectX::XMMATRIX rot = DirectX::XMMatrixIdentity();

	DecorAnimalBug(World* world, float3 spotPosition, float radius);



	virtual void update() override;

private:
	float speedRotation = 2 * PI;
};