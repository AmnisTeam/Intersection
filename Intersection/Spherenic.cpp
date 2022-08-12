#include "pch.h"
#include "Spherenic.h"


Spherenic::Spherenic(RenderWindow* renderWindow)
{
	sphere = new Sphere*[countSpheres];
	for (int x = 0; x < countSpheres; x++)
		sphere[x] = new Sphere(renderWindow);

	sphere[0]->setPosition({0, 0, 0});
	sphere[1]->setPosition({0, 0, 1});
	sphere[2]->setPosition({1, 0, 0});
	sphere[3]->setPosition({0, 0, -1});
	sphere[4]->setPosition({-1, 0, 0});
}

void Spherenic::draw(RenderTarget* renderTarget, RenderState state)
{
	state.modelMatrix = modelMatrix * state.modelMatrix;
	for (int x = 0; x < countSpheres; x++)
		renderTarget->draw(sphere[x], state);
}
