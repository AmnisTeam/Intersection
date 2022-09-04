#pragma once
#include "DecorAnimal.h"
#include "ModelsContent.h"

class DecorAnimalBug : public DecorAnimal
{
public:
	float timer = 0;

	DecorAnimalBug(World* world, float3 spotPosition, float radius);



	virtual void update() override;

private:
	

};